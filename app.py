from flask import Flask, render_template, request, redirect, session,flash
import pymysql
import re
from pymysql.err import IntegrityError

app = Flask(__name__)
app.secret_key = 'smartbank_secret_key'

# -------------------------------
# MySQL Connection Function
# -------------------------------
def get_db_connection():
    return pymysql.connect(
        host="127.0.0.1",
        user="root",
        password="",
        database="smartbank",
        port=3306,
        cursorclass=pymysql.cursors.DictCursor
    )

# -------------------------------
# ROUTES
# -------------------------------
@app.route('/', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        email = request.form['email'].strip().lower()
        password = request.form['password']

        conn = get_db_connection()
        cur = conn.cursor()

        # Check if user exists
        cur.execute("SELECT * FROM users WHERE email=%s", (email,))
        user = cur.fetchone()

        cur.close()
        conn.close()

        if not user:
            # ✅ Email not in DB
            msg = "❌ Account does not exist. Please register first."
            return render_template('message.html', msg=msg)
        elif user['password'] != password:
            # ✅ Password wrong
            msg = "❌ Incorrect password. Please try again."
            return render_template('message.html', msg=msg)
        else:
            # ✅ Success
            session['user_id'] = user['user_id']
            session['name'] = user['name']
            session['user_id'] = user['user_id']
            session['name'] = user['name']
            return redirect('/dashboard')


    # When visiting login page normally
    return render_template('login.html')

@app.route('/register', methods=['GET', 'POST'])
def register():
    error = None
    if request.method == 'POST':
        name = request.form['name'].strip()
        email = request.form['email'].strip().lower()
        password = request.form['password']

        # ✅ Email validation
        if not re.match(r'^[\w\.-]+@[\w\.-]+\.\w{2,}$', email):
            error = "Invalid email format! Please enter a valid email."
        # ✅ Password strength validation
        elif (len(password) < 8 or 
              not re.search(r'[A-Z]', password) or 
              not re.search(r'[a-z]', password) or 
              not re.search(r'\d', password) or 
              not re.search(r'[\W_]', password)):
            error = "Password must have 8+ chars, with upper, lower, digit & special char."
        else:
            conn = get_db_connection()
            cur = conn.cursor()
            try:
                cur.execute("INSERT INTO users (name, email, password) VALUES (%s, %s, %s)", 
                            (name, email, password))
                conn.commit()
                msg = "✅ Registration Successful! Please log in."
                return render_template('message.html', msg=msg)
            except IntegrityError:
                conn.rollback()
                error = "⚠️ This email is already registered."
            except Exception as e:
                conn.rollback()
                print("⚠️ MySQL Error:", e)
                error = "Unexpected database error. Please try again."
            finally:
                # ✅ Close once, safely
                cur.close()
                conn.close()

    return render_template('register.html', error=error)

@app.route('/dashboard')
def dashboard():
    if 'user_id' not in session:
        return redirect('/')
    conn = get_db_connection()
    cur = conn.cursor()
    cur.execute("SELECT * FROM accounts WHERE user_id=%s", (session['user_id'],))
    accounts = cur.fetchall()
    cur.close()
    conn.close()
    return render_template('dashboard.html', name=session['name'], accounts=accounts)


# ------------------ BANK FEATURES -------------------
@app.route('/loans')
def loans():
    if 'user_id' not in session:
        return redirect('/')

    conn = get_db_connection()
    cur = conn.cursor()
    cur.execute("""
        SELECT l.*, a.account_no 
        FROM loans l
        JOIN accounts a ON l.account_id = a.account_id
        WHERE l.user_id=%s
        ORDER BY l.start_date DESC
    """, (session['user_id'],))
    loans = cur.fetchall()
    cur.close()
    conn.close()
    return render_template('loans.html', loans=loans)

@app.route('/apply_loan', methods=['GET', 'POST'])
def apply_loan():
    if 'user_id' not in session:
        return redirect('/')

    conn = get_db_connection()
    cur = conn.cursor()
    cur.execute("SELECT account_id, account_no FROM accounts WHERE user_id=%s", (session['user_id'],))
    accounts = cur.fetchall()

    if request.method == 'POST':
        account_id = request.form['account_id']
        loan_type = request.form['loan_type']
        principal = request.form['principal']
        interest_rate = request.form['interest_rate']

        cur.execute("""
            INSERT INTO loans (user_id, account_id, loan_type, principal, interest_rate, start_date, end_date)
            VALUES (%s, %s, %s, %s, %s, CURDATE(), DATE_ADD(CURDATE(), INTERVAL 5 YEAR))
        """, (session['user_id'], account_id, loan_type, principal, interest_rate))
        conn.commit()

        cur.close()
        conn.close()
        msg = f"✅ Loan of ₹{principal} ({loan_type}) applied successfully!"
        return render_template('message.html', msg=msg)

    cur.close()
    conn.close()
    return render_template('apply_loan.html', accounts=accounts)

@app.route('/create_account', methods=['GET', 'POST'])
def create_account():
    if 'user_id' not in session:
        return redirect('/')
    if request.method == 'POST':
        acc_type = request.form['type']
        conn = get_db_connection()
        cur = conn.cursor()
        cur.execute(
            "INSERT INTO accounts (user_id, type, balance) VALUES (%s, %s, 0)",
            (session['user_id'], acc_type)
        )
        conn.commit()
        cur.close()
        conn.close()
        return redirect('/dashboard')
    return render_template('create_account.html')

@app.route('/deposit', methods=['GET', 'POST'])
def deposit():
    if 'user_id' not in session:
        return redirect('/')
    
    conn = get_db_connection()
    cur = conn.cursor()

    # Fetch only the user's accounts (with account_no)
    cur.execute("SELECT account_id, account_no, type, balance FROM accounts WHERE user_id=%s", (session['user_id'],))
    accounts = cur.fetchall()

    if request.method == 'POST':
        acc_id = request.form['acc_id']
        amount = float(request.form['amount'])

        # Verify ownership and fetch account_no
        cur.execute("SELECT account_no FROM accounts WHERE account_id=%s AND user_id=%s", (acc_id, session['user_id']))
        acc = cur.fetchone()
        if not acc:
            msg = "❌ You can only deposit into your own accounts!"
        else:
            try:
                cur.callproc('deposit', (acc_id, amount))
                conn.commit()
                msg = f"✅ ₹{amount:.2f} deposited successfully into Account {acc['account_no']}."
            except Exception as e:
                msg = f"❌ Error: {e}"

        cur.close()
        conn.close()
        return render_template('message.html', msg=msg)

    cur.close()
    conn.close()
    return render_template('deposit.html', accounts=accounts)

@app.route('/withdraw', methods=['GET', 'POST'])
def withdraw():
    if 'user_id' not in session:
        return redirect('/')
    
    conn = get_db_connection()
    cur = conn.cursor()

    # Fetch user's accounts with account_no
    cur.execute("SELECT account_id, account_no, type, balance FROM accounts WHERE user_id=%s", (session['user_id'],))
    accounts = cur.fetchall()

    if request.method == 'POST':
        acc_id = request.form['acc_id']
        amount = float(request.form['amount'])

        # Verify ownership
        cur.execute("SELECT account_no FROM accounts WHERE account_id=%s AND user_id=%s", (acc_id, session['user_id']))
        acc = cur.fetchone()
        if not acc:
            msg = "❌ You can only withdraw from your own accounts!"
        else:
            try:
                cur.callproc('withdraw', (acc_id, amount))
                conn.commit()
                msg = f"✅ ₹{amount:.2f} withdrawn successfully from Account {acc['account_no']}."
            except Exception as e:
                msg = f"❌ Error: {e}"

        cur.close()
        conn.close()
        return render_template('message.html', msg=msg)

    cur.close()
    conn.close()
    return render_template('withdraw.html', accounts=accounts)


@app.route('/transfer', methods=['GET', 'POST'])
def transfer():
    if 'user_id' not in session:
        return redirect('/')

    conn = get_db_connection()
    cur = conn.cursor()

    # Fetch user's accounts for dropdown
    cur.execute("SELECT account_id, account_no, type, balance FROM accounts WHERE user_id=%s", (session['user_id'],))
    user_accounts = cur.fetchall()

    if request.method == 'POST':
        from_acc = request.form['from_acc']
        to_acc = request.form['to_acc']
        amount = float(request.form['amount'])

        # ✅ Verify 'from' account belongs to current user
        cur.execute("SELECT account_id FROM accounts WHERE account_no=%s AND user_id=%s", (from_acc, session['user_id']))
        src = cur.fetchone()
        if not src:
            msg = "❌ You can only transfer from your own account!"
            cur.close()
            conn.close()
            return render_template('message.html', msg=msg)

        # ✅ Verify 'to' account exists
        cur.execute("SELECT account_id FROM accounts WHERE account_no=%s", (to_acc,))
        dest = cur.fetchone()
        if not dest:
            msg = "❌ Destination account number not found!"
            cur.close()
            conn.close()
            return render_template('message.html', msg=msg)

        # ✅ Prevent self-transfer
        if from_acc == to_acc:
            msg = "⚠️ You cannot transfer to the same account!"
            cur.close()
            conn.close()
            return render_template('message.html', msg=msg)

        # ✅ Call stored procedure for transfer
        try:
            cur.callproc('transfer_money', (src['account_id'], dest['account_id'], amount))
            conn.commit()
            msg = f"✅ ₹{amount:.2f} transferred successfully from A/c {from_acc} to A/c {to_acc}."
        except Exception as e:
            conn.rollback()
            msg = f"❌ Error during transfer: {e}"

        cur.close()
        conn.close()
        return render_template('message.html', msg=msg)

    cur.close()
    conn.close()
    return render_template('transfer.html', accounts=user_accounts)


@app.route('/transactions/<int:acc_id>')
def transactions(acc_id):
    if 'user_id' not in session:
        return redirect('/')
    conn = get_db_connection()
    cur = conn.cursor()
    cur.execute("SELECT account_no FROM accounts WHERE account_id=%s AND user_id=%s", (acc_id, session['user_id']))
    acc = cur.fetchone()
    if not acc:
        cur.close()
        conn.close()
        return render_template('message.html', msg="❌ You can only view your own accounts.")
    cur.execute("SELECT * FROM transactions WHERE account_id=%s ORDER BY timestamp DESC", (acc_id,))
    txns = cur.fetchall()
    cur.close()
    conn.close()
    return render_template('transactions.html', txns=txns, acc_no=acc['account_no'])

@app.route('/delete_account/<int:acc_id>', methods=['GET', 'POST'])
def delete_account(acc_id):
    if 'user_id' not in session:
        return redirect('/')

    conn = get_db_connection()
    cur = conn.cursor()

    # Verify account ownership
    cur.execute("SELECT account_id, account_no, balance FROM accounts WHERE account_id=%s AND user_id=%s",
                (acc_id, session['user_id']))
    acc = cur.fetchone()
    cur.close()
    conn.close()

    if not acc:
        return render_template('message.html', msg="❌ Account not found or unauthorized access!")

    # Render delete account options page
    return render_template('delete_account.html', acc=acc)


@app.route('/withdraw_balance/<int:acc_id>', methods=['GET'])
def withdraw_balance(acc_id):
    if 'user_id' not in session:
        return redirect('/')

    conn = get_db_connection()
    cur = conn.cursor()

    cur.execute("SELECT balance, account_no FROM accounts WHERE account_id=%s AND user_id=%s",
                (acc_id, session['user_id']))
    acc = cur.fetchone()

    if not acc:
        cur.close()
        conn.close()
        return render_template('message.html', msg="❌ Account not found!")

    if acc['balance'] <= 0:
        cur.close()
        conn.close()
        return render_template('message.html', msg="⚠️ No funds available to withdraw.")

    try:
        cur.callproc('withdraw', (acc_id, acc['balance']))
        conn.commit()
        cur.close()
        conn.close()
        # ✅ After withdrawal, redirect to delete confirmation page
        return redirect(f"/confirm_delete/{acc_id}")
    except Exception as e:
        conn.rollback()
        cur.close()
        conn.close()
        return render_template('message.html', msg=f"❌ Error: {e}")


@app.route('/transfer_balance/<int:acc_id>', methods=['GET', 'POST'])
def transfer_balance(acc_id):
    if 'user_id' not in session:
        return redirect('/')

    conn = get_db_connection()
    cur = conn.cursor()

    cur.execute("SELECT account_no, balance FROM accounts WHERE account_id=%s AND user_id=%s",
                (acc_id, session['user_id']))
    acc = cur.fetchone()

    # Get user's other accounts
    cur.execute("SELECT account_id, account_no FROM accounts WHERE user_id=%s AND account_id!=%s",
                (session['user_id'], acc_id))
    other_accs = cur.fetchall()

    if not acc:
        cur.close()
        conn.close()
        return render_template('message.html', msg="❌ Account not found!")

    if request.method == 'POST':
        to_acc_no = request.form['to_acc']
        amount = acc['balance']

        cur.execute("SELECT account_id FROM accounts WHERE account_no=%s AND user_id=%s",
                    (to_acc_no, session['user_id']))
        dest = cur.fetchone()

        if not dest:
            cur.close()
            conn.close()
            return render_template('message.html', msg="❌ Invalid destination account!")

        try:
            cur.callproc('transfer_money', (acc_id, dest['account_id'], amount))
            conn.commit()
            cur.close()
            conn.close()
            # ✅ Redirect to confirm delete after transfer
            return redirect(f"/confirm_delete/{acc_id}")
        except Exception as e:
            conn.rollback()
            cur.close()
            conn.close()
            return render_template('message.html', msg=f"❌ Error: {e}")

    cur.close()
    conn.close()
    return render_template('transfer_balance.html', acc=acc, other_accs=other_accs)


@app.route('/confirm_delete/<int:acc_id>', methods=['GET'])
def confirm_delete(acc_id):
    if 'user_id' not in session:
        return redirect('/')

    conn = get_db_connection()
    cur = conn.cursor()
    cur.execute("SELECT account_id, account_no, balance FROM accounts WHERE account_id=%s AND user_id=%s",
                (acc_id, session['user_id']))
    acc = cur.fetchone()
    cur.close()
    conn.close()

    if not acc:
        return render_template('message.html', msg="❌ Account not found or unauthorized access!")

    return render_template('confirm_delete.html', acc=acc)


@app.route('/delete_confirmed/<int:acc_id>', methods=['POST'])
def delete_confirmed(acc_id):
    if 'user_id' not in session:
        return redirect('/')

    conn = get_db_connection()
    cur = conn.cursor()

    cur.execute("SELECT account_no, balance FROM accounts WHERE account_id=%s AND user_id=%s",
                (acc_id, session['user_id']))
    acc = cur.fetchone()

    if not acc:
        msg = "❌ Account not found!"
    elif acc['balance'] > 0:
        msg = f"⚠️ Account {acc['account_no']} still has ₹{acc['balance']:.2f}. Withdraw or transfer before deleting."
    else:
        cur.execute("DELETE FROM accounts WHERE account_id=%s AND user_id=%s", (acc_id, session['user_id']))
        conn.commit()
        msg = f"✅ Account {acc['account_no']} deleted successfully."

    cur.close()
    conn.close()
    return render_template('message.html', msg=msg)


@app.route('/logout')
def logout():
    session.clear()
    return redirect('/')

# -------------------------------
# Run Flask
# -------------------------------
if __name__ == '__main__':
    app.run(debug=True)
