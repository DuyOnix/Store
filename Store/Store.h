#ifndef __STORE_H__
#define __STORE_H__
#include<iostream>
#include<fstream>
#include<iomanip>
#include<malloc.h>
#include<string.h>
#include<conio.h>
#include<stdlib.h>
#include<Windows.h>
#pragma pack(1)
#pragma warning (disable: 4996)
using namespace std;
const bool Relative = false;			// điều kiện nhập chuỗi với kích thước <= kích thước cho trước
const bool Absolute = true;				// điều kiện nhập chuỗi với kích thước =  kích thước cho trước
const bool Positive = true;				// điều kiện nhập số nguyên dương
const bool NonNegative = false;			// điều kiện nhap số nguyên không âm
struct Date								// ngày tháng năm
{
	int day;
	int month;
	int year;
};
struct Product							// sản phẩm trong cửa hàng
{
	char* id = new char[11];
	char* name = new char[31];
	char* type = new char[21];
	int price;
};
struct ProductList						// danh sách sản phẩm trong cửa hàng
{
	int size;
	Product* list;
};
struct Staff							// nhân viên
{
	char id[11];
	char username[21];
	char password[21];
	char fullName[31];
};		
struct StaffList						// danh sách nhân viên
{
	int size;
	Staff* list;
};
struct OrderProduct						// sản phẩm trong đơn hàng
{
	char product[31];
	int price;
	int amount;
};
struct Order							// đơn hàng
{
	char createDay[11];
	long long totalPrice;
	int amountProducts;
	OrderProduct* orderList;
};
struct OrderList						// tổng danh sách đơn hàng
{
	int amountOrders;
	Order* totalList;
};
void gotoxy(int x, int y);												// di chuyển đến tọa độ bất kì trong console
bool isNumber(char* src, int& num);										// kiểm tra chuỗi nhập có phải là số hay không
bool isLeapYear(int year);												// kiểm tra năm nhuận
bool isDate(Date date);													// kiểm tra ngày nhập có phù hợp không
void inputString(char* des, int size, bool isAbsolute);					// nhập chuỗi với điều kiện kích thước cho trước
void inputDate(char* des);												// nhập ngày
void inputPassword(char* des, int size);								// nhập mật khẩu
void inputNumber(int& num, bool isPositive);							// nhập số phù hợp với điều kiện cho trước
bool logIn(StaffList lst);												// đăng nhập
void loadProductList(const char* fileName, ProductList& lst);			// tải lên danh sách sản phẩm trong cửa hàng
void loadStaffList(const char* fileName, StaffList& lst);				// tải lên danh sách nhân viên trong cửa hàng	
void loadOrderList(const char* fileName, OrderList& odl);				// tải lên danh sách hóa đơn và doanh thu
void saveProductList(const char* fileName, ProductList lst);			// lưu lại danh sách sản phẩm trong cửa hàng
void saveStaffList(const char* fileName, StaffList lst);				// lưu lại danh sách nhân viên trong cửa hàng
void saveOrderList(const char* fileName, OrderList odl);				// lưa lại danh sách hóa đơn và doanh thu
void makeProduct(Product& prd, char* code = NULL);						// tạo sản phẩm 
bool findIndexOfProduct(ProductList lst, char* code, int& index);		// tìm vị trí sản phẩm với mã cho trước trong danh sách
void showProduct(Product prd);											// hiển thị thông tin sản phẩm
void showProductList(ProductList lst);									// hiển thị danh sách sản phẩm
bool insertProduct(ProductList& lst);									// thêm sản phẩm vào danh sách
bool eraseProduct(ProductList& lst, char* code);						// xóa sản phẩm khỏi danh sách
void editProduct(ProductList& lst, char* code);							// chỉnh sửa sản trong danh sách
void makeStaff(Staff& stf, char* code = NULL);							// tạo nhân viên
bool findIndexOfStaff(StaffList lst, char* code, int& index);			// tìm vị trí nhân viên với mã cho trước trong danh sách
void showStaff(Staff stf);												// hiển thị thông tin nhân viên
void showStaffList(StaffList lst);										// hiển thị danh sách nhân viên
bool insertStaff(StaffList& lst);										// thêm nhân viên vào danh sách
bool eraseStaff(StaffList& lst, char* code);							// xóa nhân viên khỏi danh sách
void editStaff(StaffList& lst, char* code);								// chỉnh sửa nhân viên trong danh sách
void makeOrderProduct(OrderProduct& odp, ProductList prl);				// tạo danh sách sản phẩm trong đơn hàng		
void showOrderProduct(OrderProduct odp);								// hiển thị danh sách sản phẩm trong đơn hàng
void makeOrder(Order& ord, ProductList prl);							// tạo đơn hàng
void insertOrder(OrderList& odl, ProductList prl);						// thêm đơn hàng vào trong danh sách
void showOrder(Order ord);												// hiển thị thông tin đơn hàng
bool isDayinOrderList(OrderList odl, char* day);						// kiểm tra ngày cho trước có tồn tại trong danh sách đơn hàng không
void showListOrderWithDay(OrderList odl, char* day);					// hiển thị danh sách đơn hàng với ngày cho trước
void destroyProductList(ProductList& lst);								// thu hồi vùng nhớ của danh sách sản phẩm
void destroyStaffList(StaffList& lst);									// thu hồi vùng nhớ của danh sách nhân viên
void destroyOrderList(OrderList& odl);									// thu hồi vùng nhớ của danh sách đơn hàng
int mainMenu();															// MENU chính ban đầu 
int storeMenu();														// MENU cửa hàng
int productMenu();														// MENU sản phẩm
int staffMenu();														// MENU nhân viên
int Choice(int max);													// nhập lựa chọn
void runStore(ProductList& prl, StaffList& stl, OrderList& odl);		// chạy các chức năng trong cửa hàng
void runProgram();														// chạy chương trình gốc

#endif
