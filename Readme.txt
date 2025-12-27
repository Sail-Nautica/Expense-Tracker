Author: Amit Sail
"Go Blue!"

This is the Readme file for my first project Expense Tracker.

This project will focus on me developing a practical understanding of the following topics:
- Git
- Data Modelling
- CRUD Operations
- File Persistance
- Input Validation
- Analytics
- User Interface/Experience

Purpose of the project:
Build an app to help me 
- Record Expenses and Income
- Categorize Items
- Summarize Spending/Earning
- Create and View Budgets

Design Specifications for Minimal Viable Product:

Transactions
- Add Transactions w/
    Dollar Amount
    Type (Spending/Earning)
    Category
    Date
    Description
    Payment Method
- Edit Transaction
- Delete Transaction
- List Transactions w/ Sorting

Categories
- Default List w/ Food, Transport, Online Spending
- Add/Edit/Delete Categories

Views
- All Transaction View w/
    Filter by Date
    Filter by Category
    Filter by Text
- Summary View w/
    Total Expenses/Earning For Month
    Net Money
    Top Categories

Data
- Must be saved locally

Design Specifications for V2

Budgets
- Monthly Budgets per Category
- Recurring transactions
- Import/Export CSV

Quality Of Life Additions
- Basic Charts
- Multi Account Support
- Photo Integration

Data Model
Transaction 
- id                (UUID)
- ammount_cents     (int)
- currency          (string)
- type              (string)["expense", "income", "transfer"]
- category_id       (string)
- timestamp         (ISO String)
- note              (string)
- merchant          (string)
- account_id        (optional int)

Category
- id                (UUID)
- Name              (String)

Budgets
- id                (UUID)
- category_id       (UUID)
- month             (YYYY-MM)
- limit_cents       (int)

Account
- id                (UUID)
- name              (string)
- type              (string)


Architecture
- UI Layer
    Web Frontend
- Service Layer
- Data Access Layer
- Models


