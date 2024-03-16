#include <bits/stdc++.h>
using namespace std;

class Product {
public:
    int id;
    string name;
    string description;
    double price;
    unordered_map<string, string> attributes; // For storing additional attributes like color,size etc.

    Product(int id, string name, string description, double price) : id(id), name(name), description(description), price(price) {}
};

class Category {
public:
    int id;
    string name;
    int parent_id;

    Category(int id, string name, int parent_id = -1) : id(id), name(name), parent_id(parent_id) {}
};

class ProductDatabase {
private:
    unordered_map<int, Product> products;
    unordered_map<int, Category> categories;

public:
    void addProduct(Product product){
        products[product.id]=product;
    }

    void addCategory(Category category){
        categories[category.id]=category;
    }

    vector<Product> searchProductsByKeyword(string keyword){
        vector<Product> results;
        for(const auto& x : products){
            const Product& product = x.second;
            if(product.name.find(keyword) != string::npos || product.description.find(keyword) != string::npos){
                results.push_back(product);
            }
        }
        return results;
    }

    vector<Product> searchProductsByCategory(int categoryId){
        vector<Product> results;
        for(const auto& pair : products){
            const Product& product = pair.second;
            if(product.attributes.count("category") > 0 && stoi(product.attributes.at("category")) == categoryId){
                results.push_back(product);
            }
        }
        return results;
    }

};

int main(){
    ProductDatabase db;

    // Adding categories
    Category electronics(1, "Electronics");
    Category books(2, "Books");
    db.addCategory(electronics);
    db.addCategory(books);

    // Adding products
    Product smartphone(101, "Smartphone", "A high-end smartphone", 999.99);
    smartphone.attributes["category"] = "1";
    Product laptop(102, "Laptop", "A powerful laptop for professionals", 1499.99);
    laptop.attributes["category"] = "1";
    Product pythonBook(201, "Python Programming", "A comprehensive guide to Python programming", 29.99);
    pythonBook.attributes["category"] = "2";
    db.addProduct(smartphone);
    db.addProduct(laptop);
    db.addProduct(pythonBook);

    // Search products by keyword
    cout << "Search results for 'python':" << endl;
    vector<Product> pythonResults = db.searchProductsByKeyword("python");
    for(const auto& product : pythonResults){
        cout<<product.name<<endl;
    }

    // Search products by category
    cout<<"\nSearch results for category 'Electronics':" << endl;
    vector<Product> electronicsResults = db.searchProductsByCategory(1);
    for(const auto& product : electronicsResults){
        cout<<product.name<<endl;
    }
    return 0;
}
