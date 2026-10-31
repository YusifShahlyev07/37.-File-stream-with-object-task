#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>
#include <sstream>
using namespace std;
#pragma region Book Management System
class Book {
private:
	int id;
	string title;
	string author;
	double price;
public:
	Book() = default;
	Book(int id, string title, string author, double price) {
		this->id = id;
		this->title = title;
		this->author = author;
		this->price = price;
	}
	// Getters
	int GetId() const {
		return id;
	}
	string GetTitle() const {
		return title;
	}
	string GetAuthor() const {
		return author;
	}
	double GetPrice() const {
		return price;
	}
	// Setters
	void SetId(int id) {
		if(id>0)
			this->id = id;
	}
	void SetTitle(string title) {
		if(title.length()>3)
			this->title = title;
	}
	void SetAuthor(string author) {
		if(author.length()>3)
			this->author = author;
	}
	void SetPrice(double price) {
		if (price >= 0) {
			this->price = price;
		}
	}
	void Show() const {
		cout << "ID: " << id << endl;
		cout << "Title: " << title << endl;
		cout << "Author: " << author << endl;
		cout << "Price: " << price << " AZN" << endl;
	}
};
class Database {
private:
	vector<Book> books;
public:
	// ID-nin movcud olub-olmadigini yoxlayir
	bool Exists(int id) const {
		for (const Book& book : books) {
			if (book.GetId() == id) {
				return true;
			}
		}
		return false;
	}
	// Create
	void AddBook(Book book) {
		if (Exists(book.GetId())) {
			cout << "This ID already exists!" << endl;
			return;
		}
		if (book.GetPrice() < 0) {
			cout << "Price cannot be negative!" << endl;
			return;
		}
		books.push_back(book);
		cout << "Book added successfully!" << endl;
	}
	// Read all books
	void ShowBooks() const {
		if (books.empty()) {
			cout << "No books found!" << endl;
			return;
		}
		for (const Book& book : books) {
			cout << "------------------------" << endl;
			book.Show();
		}
	}
	// Search by ID
	void SearchBook(int id) const {
		for (const Book& book : books) {
			if (book.GetId() == id) {
				book.Show();
				return;
			}
		}
		cout << "Book not found!" << endl;
	}
	// Update
	void UpdateBook(int id) {
		for (Book& book : books) {
			if (book.GetId() == id) {
				string title, author;
				double price;
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "New title: ";
				getline(cin, title);
				cout << "New author: ";
				getline(cin, author);
				cout << "New price: ";
				cin >> price;
				if (cin.fail()) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Invalid price!" << endl;
					return;
				}
				if (price < 0) {
					cout << "Price cannot be negative!" << endl;
					return;
				}
				book.SetTitle(title);
				book.SetAuthor(author);
				book.SetPrice(price);
				cout << "Book updated successfully!" << endl;
				return;
			}
		}
		cout << "Book not found!" << endl;
	}
	// Delete
	void DeleteBook(int id) {
		for (int i = 0; i < books.size(); i++) {
			if (books[i].GetId() == id) {
				books.erase(books.begin() + i);
				cout << "Book deleted successfully!" << endl;
				return;
			}
		}
		cout << "Book not found!" << endl;
	}

	void WriteToFile(string path = "books.txt") {
		ofstream fs(path,ios::out);

		if (!fs.is_open()) {
			cout << "File didn't open" << endl;
			return;
		}

		for (const Book& book : books)
		{
			fs << book.GetId()<<'#';
			fs << book.GetAuthor() << '#';
			fs << book.GetPrice() << '#';
			fs << book.GetTitle();
		}
		fs.close();
	}

	void ReadFromFile(string path = "books.txt") {
		ifstream fs(path);

		if (!fs.is_open()) {
			cout << "File didn't open";
			return;
		}
		string row;
		while (getline(fs, row)) {
			stringstream ss(row);
			string str_id, author, str_price, title;

			getline(ss, str_id, '#');
			getline(ss, author, '#');
			getline(ss, str_price, '#');
			getline(ss, title);

			double price = stod(str_price);
			int id = stoi(str_id);

			Book book(id, title, author, price);
			books.push_back(book);
		}
	}
};

int main() {
	Database db;
	int choice;
	db.ReadFromFile();
	do {
		cout << "\n===== BOOK MANAGEMENT SYSTEM =====\n";
		cout << "1. Show all books\n";
		cout << "2. Add book\n";
		cout << "3. Search book by ID\n";
		cout << "4. Update book\n";
		cout << "5. Delete book\n";
		cout << "0. Exit\n";
		cout << "Choose: ";
		cin >> choice;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid input!" << endl;
			continue;
		}
		switch (choice) {
		case 1:
			db.ShowBooks();
			break;
		case 2: {
			int id;
			string title, author;
			double price;
			cout << "ID: ";
			cin >> id;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Title: ";
			getline(cin, title);
			cout << "Author: ";
			getline(cin, author);
			cout << "Price: ";
			cin >> price;
			if (cin.fail()) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Invalid price!" << endl;
				break;
			}
			if (price < 0) {
				cout << "Price cannot be negative!" << endl;
				break;
			}
			db.AddBook(Book(id, title, author, price));
			break;
		}
		case 3: {
			int id;
			cout << "Enter book ID: ";
			cin >> id;
			if (cin.fail()) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Invalid ID!" << endl;
				break;
			}
			db.SearchBook(id);
			break;
		}
		case 4: {
			int id;
			cout << "Enter book ID to update: ";
			cin >> id;
			if (cin.fail()) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Invalid ID!" << endl;
				break;
			}
			db.UpdateBook(id);
			break;
		}
		case 5: {
			int id;
			cout << "Enter book ID to delete: ";
			cin >> id;
			if (cin.fail()) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Invalid ID!" << endl;
				break;
			}
			db.DeleteBook(id);
			break;
		}
		case 0:
			cout << "Goodbye!" << endl;
			break;
		default:
			cout << "Wrong choice!" << endl;
		}
		db.WriteToFile();
	} while (choice != 0);
	return 0;
}
#pragma endregion