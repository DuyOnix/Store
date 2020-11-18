#include "Store.h"

void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

bool isNumber(char* src, int& num)
{
	for (int i = 0; i < strlen(src); i++)
	{
		if (src[i] < '0' || src[i]>'9')
		{
			num = 0;
			return false;
		}
	}
	num = atoi(src);
	return true;
}

bool isLeapYear(int year)
{
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

bool isDate(Date date)
{
	bool checkDate = true;
	bool leap = isLeapYear(date.year);
	if (date.month < 1 || date.month>12)
		return false;
	switch (date.month)
	{
	case 1: case 3: case 5: case 7: case 8: case 10: case 12:
		if (date.day < 1 || date.day>31)
			checkDate = false;
		break;
	case 4: case 6: case 9: case 11:
		if (date.day < 1 || date.day>30)
			checkDate = false;
		break;
	default:
		if (leap)
		{
			if (date.day < 1 || date.day>29)
				checkDate = false;
		}
		else
		{
			if (date.day < 1 || date.day>28)
				checkDate = false;
		}
	}
	return checkDate;
}

void inputString(char* des, int size, bool isAbsolute)
{
	char* tmp = new char[50];
	cin.getline(tmp,50);
	if (isAbsolute)
	{
		while (strlen(tmp) != size)
		{
		strcpy(tmp, "");
		cout << "-> Nhap sai kich thuoc (kthuoc = " << size << ") !!!\n";
		cout << "- Moi ban nhap lai : ";
		cin.getline(tmp, 50);
		}
	}
	else
	{
		while (strlen(tmp) > size)
		{
			strcpy(tmp, "");
			cout << "-> Nhap qua kich thuoc (0 < kthuoc <= " << size << ") !!!\n";
			cout << "- Moi ban nhap lai : ";
			cin.getline(tmp, 50);
		}
	}
	strcpy(des, tmp);
	delete[] tmp;
}

void inputDate(char* des)
{
	Date date;
	char* tmp = new char[50];
	cin.getline(tmp, 50);
	char day[3], month[3], year[5];
	int index = 0;
	bool checkDay, checkMonth, checkYear;
	for (int i = 0; i < 2; i++)
		day[i] = tmp[index++];
	day[2] = '\0';
	index++;
	for (int i = 0; i < 2; i++)
		month[i] = tmp[index++];
	month[2] = '\0';
	index++;
	for (int i = 0; i < 4; i++)
		year[i] = tmp[index++];
	year[4] = '\0';
	checkDay = isNumber(day, date.day);
	checkMonth = isNumber(month, date.month);
	checkYear = isNumber(year, date.year);
	while (strlen(tmp) != 10 || tmp[2] != '/' || tmp[5] != '/' || !checkDay || !checkMonth || !checkYear || !isDate(date))
	{
		index = 0;
		strcpy(tmp, "");
		strcpy(day, "");
		strcpy(month, "");
		strcpy(year, "");
		cout << "-> Nhap sai dinh dang ngay (dd/mm/yyyy) hoac sai ngay !!!\n";
		cout << "- Moi ban nhap lai : ";
		cin.getline(tmp, 50);
		for (int i = 0; i < 2; i++)
			day[i] = tmp[index++];
		day[2] = '\0';
		index++;
		for (int i = 0; i < 2; i++)
			month[i] = tmp[index++];
		month[2] = '\0';
		index++;
		for (int i = 0; i < 4; i++)
			year[i] = tmp[index++];
		year[4] = '\0';
		checkDay = isNumber(day, date.day);
		checkMonth = isNumber(month, date.month);
		checkYear = isNumber(year, date.year);
	}
	strcpy(des, tmp);
	delete[] tmp;
}

void inputPassword(char* des, int size)
{
	char* a = new char[50];
	char c;
	int i = 0;
	while (1)
	{
		c = getch();
		if (c != 8 && c != 13)
		{
			cout << "*";
			a[i++] = c;
		}
		else if (c == 8)
		{
			if (i == 0)
				continue;
			else
			{
				cout << "\b \b";
				i--;
			}
		}
		else if (c == 13)
		{
			a[i] = '\0';
			cout << endl;
			break;
		}
	}
	while (strlen(a) > size)
	{
		strcpy(a, "");
		cout << "-> Nhap qua kich thuoc (0 < kthuoc <= " << size << ") !!!\n";
		cout << "- Moi ban nhap lai mat khau: ";
		while (1)
		{
			c = getch();
			if (c != 8 && c != 13)
			{
				cout << "*";
				a[i++] = c;
			}
			else if (c == 8)
			{
				cout << "\b \b";
				i--;
			}
			else if (c == 13)
			{
				a[i] = '\0';
				cout << endl;
				break;
			}
		}
	}
	strcpy(des, a);
	delete[] a;
}

void inputNumber(int& num, bool isPositive)
{
	bool isNumber = true;
	char* input = new char[20];
	cin.getline(input, 20);
	for (int i = 0; i < strlen(input); i++)
	{
		if (input[i] < '0' || input[i] > '9')
		{
			isNumber = false;
			break;
		}
	}
	while (!isNumber)
	{
		isNumber = true;
		strcpy(input, "");
		cout << "-> Nhap sai gia tri!!!\n";
		cout << "- Moi ban nhap lai: ";
		cin.getline(input, 20);
		for (int i = 0; i < strlen(input); i++)
		{
			if (input[i] < '0' || input[i] > '9')
			{
				isNumber = false;
				break;
			}
		}
	}
	if (isPositive)
		num = atoi(input);
	delete[] input;
}

bool logIn(StaffList lst)
{
	bool check = false;
	char* name = new char[51];
	char* pass = new char[51];
	gotoxy(40, 10);
	cout << "- Ten dang nhap: ";
	inputString(name, 50, Relative);
	gotoxy(40, 12);
	cout << "- Mat khau     : ";
	inputPassword(pass, 50);
	for (int i = 0; i < lst.size; i++)
	{
		if ((strcmp(lst.list[i].username, name) == 0 && 
			strcmp(lst.list[i].password, pass) == 0) || (strcmp(name, "admin") == 0 && strcmp(pass, "admin") == 0))
		{
			check = true;
			break;
		}
	}
	delete[] name;
	delete[] pass;
	return check;
}

void loadProductList(const char* fileName, ProductList& lst)
{
	ifstream file(fileName, ios::in | ios::binary);
	if (file.fail())
		return;
	file.read((char*)&lst.size, sizeof(int));
	lst.list = new Product[lst.size];
	for (int i = 0; i < lst.size; i++)
	{
		file.read(lst.list[i].id, 11);
		file.read(lst.list[i].name, 31);
		file.read(lst.list[i].type, 21);
		file.read((char*)&lst.list[i].price, sizeof(int));
	}
	file.close();
}

void loadStaffList(const char* fileName, StaffList& lst)
{
	ifstream file(fileName, ios::in | ios::binary);
	if (file.fail())
		return;
	file.read((char*)&lst.size, sizeof(int));
	lst.list = new Staff[lst.size];
	for (int i = 0; i < lst.size; i++)
		file.read((char*)&lst.list[i], sizeof(Staff));
	file.close();
}

void loadOrderList(const char* fileName, OrderList& odl)
{
	ifstream file(fileName, ios::in | ios::binary);
	if (file.fail())
		return;
	file.read((char*)&odl.amountOrders, sizeof(int));
	odl.totalList = new Order[odl.amountOrders];
	for (int i = 0; i < odl.amountOrders; i++)
	{
		file.read((char*)&odl.totalList[i].createDay, 11);
		file.read((char*)&odl.totalList[i].totalPrice, sizeof(long long));
		file.read((char*)&odl.totalList[i].amountProducts, sizeof(int));
		odl.totalList[i].orderList = new OrderProduct[odl.totalList[i].amountProducts];
		for (int j = 0; j < odl.totalList[i].amountProducts; j++)
		{
			file.read((char*)&odl.totalList[i].orderList[j], sizeof(OrderProduct));
		}
	}
	file.close();
}

void saveProductList(const char* fileName, ProductList lst)
{

	ofstream file(fileName, ios::out | ios::binary);
	if (file.fail())
		return;
	file.write((char*)&lst.size, sizeof(int));
	for (int i = 0; i < lst.size; i++)
	{
		file.write((char*)&lst.list[i].id, 11);
		file.write((char*)&lst.list[i].name, 31);
		file.write((char*)&lst.list[i].type, 21);
		file.write((char*)&lst.list[i].id, sizeof(int));
	}
	file.close();
}

void saveStaffList(const char* fileName, StaffList lst)
{
	ofstream file(fileName, ios::out | ios::binary);
	if (file.fail())
		return;
	file.write((char*)&lst.size, sizeof(int));
	for (int i = 0; i < lst.size; i++)
		file.write((char*)&lst.list[i], sizeof(Staff));
	file.close();
}

void saveOrderList(const char* fileName, OrderList odl)
{
	ofstream file(fileName, ios::out | ios::binary);
	if (file.fail())
		return;
	file.write((char*)&odl.amountOrders, sizeof(int));
	for (int i = 0; i < odl.amountOrders; i++)
	{
		file.write((char*)&odl.totalList[i].createDay, 11);
		file.write((char*)&odl.totalList[i].totalPrice, sizeof(long long));
		file.write((char*)&odl.totalList[i].amountProducts, sizeof(int));
		for (int j = 0; j < odl.totalList[i].amountProducts; j++)
		{
			file.write((char*)&odl.totalList[i].orderList[j], sizeof(OrderProduct));
		}
	}
	file.close();
}

void makeProduct(Product& prd, char* code)
{
	if (code == NULL)
	{
		cout << "- Nhap ma (dung 10 ki tu): ";
		inputString(prd.id, 10, Absolute);
	}
	else
		strcpy(prd.id, code);
	cout << "- Nhap ten: ";
	inputString(prd.name, 30, Relative);
	cout << "- Nhap loai: ";
	inputString(prd.type, 20, Relative);
	cout << "- Nhap gia ban: ";
	inputNumber(prd.price, Positive);
}

bool findIndexOfProduct(ProductList lst, char* code, int& index)
{
	if (lst.list == NULL || lst.size == 0)
		return false;
	for (int i = 0; i < lst.size; i++)
	{
		if (strcmp(lst.list[i].id, code) == 0)
		{
			index = i;
			return true;
		}
	}
	return false;
}

void showProduct(Product prd)
{
	cout << setw(15) << left << prd.id << setw(35) << prd.name << setw(25) << prd.type << setw(15) << right << prd.price << " VND" << endl;
}

void showProductList(ProductList lst)
{
	cout << "                     --->		  DANH SACH SAN PHAM        <---" << endl;
	cout << setw(15) << left << "Ma" << setw(35) << "Ten" << setw(25) << "Loai" << setw(19) << right << "Gia ban" << endl;
	cout << "------------------------------------------------------------------------------------------------\n";
	for (int i = 0; i < lst.size; i++)
		showProduct(lst.list[i]);
}

bool insertProduct(ProductList& lst)
{
	Product prd;
	cout << "--> Nhap thong tin san pham them vao danh sach" << endl;
	cin.ignore();
	makeProduct(prd);
	for (int i = 0; i < lst.size; i++)
	{
		if (strcmp(prd.id, lst.list[i].id) == 0)
			return false;
	}
	if (lst.list == NULL || lst.size == 0)
	{
		lst.list = new Product;
		lst.list[0] = prd;
		lst.size = 1;
	}
	else
	{
		int newSize = lst.size + 1;
		Product* newList = (Product*)realloc(lst.list, newSize * sizeof(Product));
		lst.list = newList;
		lst.list[lst.size] = prd;
		lst.size = newSize;
	}
	return true;
}

bool eraseProduct(ProductList& lst, char* code)
{
	if (lst.list == NULL || lst.size == 0)
		return false;
	int index;
	bool isExist = findIndexOfProduct(lst, code, index);
	if (!isExist)
		return false;
	for (int i = index; i < lst.size - 1; i++)
	{
		lst.list[i] = lst.list[i + 1];
	}
	int newSize = lst.size - 1;
	Product* newList = (Product*)realloc(lst.list, newSize * sizeof(Product));
	lst.list = newList;
	lst.size = newSize;
	return true;
}

void editProduct(ProductList& lst, char* code)
{
	if (lst.list == NULL || lst.size == 0)
	{
		cout << "-> Danh sach san pham rong!!!\n";
		return;
	}
	int index;
	bool isExist = findIndexOfProduct(lst, code, index);
	if (!isExist)
	{
		cout << "-> Khong tim thay san pham voi ma vua nhap trong danh sach!!!\n";
		return;
	}
	Product prd;
	cout << "--> Chinh sua thong tin san pham" << endl;
	makeProduct(prd, code);
	for (int i = 0; i < lst.size; i++)
	{
		if (i == index)
			continue;
		if (strcmp(prd.id, lst.list[i].id) == 0)
		{
			cout << "-> Ma san pham vua nhap da ton tai trong danh sach!!!\n";
			return;
		}
	}
	lst.list[index] = prd;
	cout << "-> Da chinh sua xong san pham\n";
}

void makeStaff(Staff& stf, char* code)
{
	if (code == NULL)
	{
		cout << "- Nhap ma (dung 10 ki tu): ";
		inputString(stf.id, 10, Absolute);
	}
	else
		strcpy(stf.id, code);
	char* checkPass = new char[21];
	cout << "- Nhap ten dang nhap: ";
	inputString(stf.username, 20, Relative);
	cout << "- Nhap mat khau     : ";
	inputPassword(stf.password, 20);
	cout << "- Nhap lai mat khau : ";
	inputPassword(checkPass, 20);
	while (strcmp(stf.password, checkPass) != 0)
	{
		cout << "-> Hai mat khau ban nhap khong khop nhau!!! Moi ban nhap lai\n";
		cout << "- Nhap mat khau     : ";
		inputPassword(stf.password, 20);
		cout << "- Nhap lai mat khau : ";
		inputPassword(checkPass, 20);
	}
	cout << "- Nhap ho ten		 : ";
	inputString(stf.fullName, 30, Relative);
	delete[] checkPass;
}

bool findIndexOfStaff(StaffList lst, char* code, int& index)
{
	if (lst.list == NULL || lst.size == 0)
		return false;
	for (int i = 0; i < lst.size; i++)
	{
		if (strcmp(lst.list[i].id, code) == 0)
		{
			index = i;
			return true;
		}
	}
	return false;
}

void showStaff(Staff stf)
{
	cout << setw(15) << left << stf.id << setw(25) << stf.username << setw(25) << stf.password << setw(35) << stf.fullName << endl;
}

void showStaffList(StaffList lst)
{
	cout << "               --->		 DANH SACH NHAN VIEN        <---" << endl;
	cout << setw(15) << left << "Ma" << setw(25) << "Ten dang nhap" << setw(25) << "Mat khau" << setw(35) << "Ho ten" << endl;
	cout << "-----------------------------------------------------------------------------------\n";
	for (int i = 0; i < lst.size; i++)
		showStaff(lst.list[i]);
}

bool insertStaff(StaffList& lst)
{
	Staff stf;
	cout << "--> Nhap thong tin nhan vien them vao danh sach" << endl;
	cin.ignore();
	makeStaff(stf);
	for (int i = 0; i < lst.size; i++)
	{
		if (strcmp(stf.id, lst.list[i].id) == 0)
			return false;
	}
	if (lst.list == NULL || lst.size == 0)
	{
		lst.list = new Staff;
		lst.list[0] = stf;
		lst.size = 1;
	}
	else
	{
		int newSize = lst.size + 1;
		Staff* newList = (Staff*)realloc(lst.list, newSize * sizeof(Staff));
		lst.list = newList;
		lst.list[lst.size] = stf;
		lst.size = newSize;
	}
	return true;
}

bool eraseStaff(StaffList& lst, char* code)
{
	if (lst.list == NULL || lst.size == 0)
		return false;
	int index;
	bool isExist = findIndexOfStaff(lst, code, index);
	if (!isExist)
		return false;
	for (int i = index; i < lst.size - 1; i++)
	{
		lst.list[i] = lst.list[i + 1];
	}
	int newSize = lst.size - 1;
	Staff* newList = (Staff*)realloc(lst.list, newSize * sizeof(Staff));
	lst.list = newList;
	lst.size = newSize;
	return true;
}

void editStaff(StaffList& lst, char* code)
{
	if (lst.list == NULL || lst.size == 0)
	{
		cout << "-> Danh sach nhan vien rong!!!\n";
		return;
	}
	int index;
	bool isExist = findIndexOfStaff(lst, code, index);
	if (!isExist)
	{
		cout << "-> Khong tim thay nhan vien voi ma vua nhap trong danh sach!!!\n";
		return;
	}
	Staff stf;
	cout << "--> Chinh sua thong tin nhan vien" << endl;
	makeStaff(stf, code);
	for (int i = 0; i < lst.size; i++)
	{
		if (i == index)
			continue;
		if (strcmp(stf.id, lst.list[i].id) == 0)
		{
			cout << "-> Ma nhan vien vua nhap da ton tai trong danh sach!!!\n";
			return;
		}
	}
	lst.list[index] = stf;
	cout << "-> Da chinh sua xong nhan vien\n";
}

void makeOrderProduct(OrderProduct& odp, ProductList prl)
{
	bool isExist;
	int index;
	char* code = new char[11];
	cout << "- Nhap ma (dung 10 ki tu): ";
	inputString(code, 10, Absolute);
	isExist = findIndexOfProduct(prl, code, index);
	if (!isExist)
	{
		cout << "-> Ma ban nhap khong ton tai trong danh sach san pham!!!!\n";
		cout << "- Moi ban nhap lai ma: ";
		inputString(code, 10, Absolute);
		isExist = findIndexOfProduct(prl, code, index);
	}
	strcpy(odp.product, prl.list[index].name);
	cout << "- Ten san pham : " << odp.product << endl;
	odp.price = prl.list[index].price;
	cout << "- Gia tien     : " << odp.price << " VND\n";
	cout << "- Nhap so luong: ";
	inputNumber(odp.amount, Positive);
}

void showOrderProduct(OrderProduct odp)
{
	cout << setw(35) << left << odp.product << setw(15) << right << odp.price << " VND" << setw(11) << odp.amount << endl;
}

void makeOrder(Order& ord, ProductList prl)
{
	cout << "--> Nhap ngay tao (dd/mm/yyyy): ";
	cin.ignore();
	inputDate(ord.createDay);
	cout << "--> Nhap so luong san pham: ";
	cin >> ord.amountProducts;
	cin.ignore();
	ord.orderList = new OrderProduct[ord.amountProducts];
	for (int i = 0; i < ord.amountProducts; i++)
	{
		cout << "-> Nhap san pham thu " << i + 1 << ": " << endl;
		makeOrderProduct(ord.orderList[i], prl);
	}
	ord.totalPrice = 0;
	for (int i = 0; i < ord.amountProducts; i++)
	{
		ord.totalPrice += (long long)ord.orderList[i].price * ord.orderList[i].amount;
	}
}

void insertOrder(OrderList& odl, ProductList prl)
{
	Order ord;
	cout << "          Nhap DON HANG" << endl;
	makeOrder(ord, prl);
	if (odl.totalList == NULL || odl.amountOrders == 0)
	{
		odl.totalList = &ord;
		odl.amountOrders = 1;
	}
	else
	{
		int newSize = odl.amountOrders + 1;
		Order* newList = (Order*)realloc(odl.totalList, newSize * sizeof(OrderProduct));
		odl.totalList = newList;
		odl.totalList[odl.amountOrders] = ord;
		odl.amountOrders = newSize;
	}
}

void showOrder(Order ord)
{
	cout << "- Ngay tao: " << ord.createDay << endl;
	cout << "_____________________________________________________________________" << endl;
	cout << setw(37) << left << "San pham" << setw(19) << right << "So tien" << setw(13) << "So luong\n\n";
	for (int i = 0; i < ord.amountProducts; i++)
	{
		cout << i + 1 << ".";
		showOrderProduct(ord.orderList[i]);
	}
	cout << "_____________________________________________________________________" << endl;
	cout << "===> Tong tien: "<<setw(5) << ord.totalPrice << endl;
	cout << "----------------------------------------------------------------------\n";
}

bool isDayinOrderList(OrderList odl, char* day)
{
	for (int i = 0; i < odl.amountOrders; i++)
	{
		if (strcmp(odl.totalList[i].createDay, day) == 0)
			return true;
	}
	return false;
}

void showListOrderWithDay(OrderList odl, char* day)
{
	bool isValidDay = isDayinOrderList(odl, day);
	if (!isValidDay)
	{
		cout << "--> Khong co don hang nao trong ngay " << day << endl;
		return;
	}
	int index = 1;
	long long totalMoney = 0;
	cout << "	   ========  DANH SACH HOA DON NGAY " << day << "   ========\n";
	cout << "----------------------------------------------------------------------\n";
	for (int i = 0; i < odl.amountOrders; i++)
	{
		if (strcmp(odl.totalList[i].createDay, day) == 0)
		{
			cout << "                             DON HANG " << index++ << endl;
			showOrder(odl.totalList[i]);
			totalMoney += odl.totalList[i].totalPrice;
		}
	}
	cout << "          =======>  TONG DOANH THU: " << totalMoney << " VND  <=======\n";
}

void destroyProductList(ProductList& lst)
{
	delete[] lst.list;
}

void destroyStaffList(StaffList& lst)
{
	delete[] lst.list;
}

void destroyOrderList(OrderList& odl)
{
	for (int i = 0; i < odl.amountOrders; i++)
	{
		delete[] odl.totalList[i].orderList;
	}
	delete[] odl.totalList;
}

int mainMenu()
{
	cout << "-------------MENU-------------\n";
	cout << "1. Dang nhap\n";
	cout << "2. Thoat chuong trinh\n";
	cout << "------------------------------\n";
	return 2;
}

int storeMenu()
{
	cout << "----------------MENU CUA HANG-----------------\n";
	cout << "1. Chinh sua danh sach san pham\n";
	cout << "2. Chinh sua danh sach nhan vien\n";
	cout << "3. Tao don hang\n";
	cout << "4. Thong ke so luong don hang va tong doanh thu theo ngay\n";
	cout << "5. Dang xuat\n";
	cout << "------------------------------------------------\n";
	return 5;
}

int productMenu()
{
	cout << "----------------MENU SAN PHAM-----------------\n";
	cout << "1. Hien thi danh sach san pham\n";
	cout << "2. Them san pham vao danh sach\n";
	cout << "3. Xoa san pham khoi danh sach\n";
	cout << "4. Sua san pham trong danh sach\n";
	cout << "5. Quay lai\n";
	cout << "----------------------------------------------\n";
	return 5;
}

int staffMenu()
{
	cout << "----------------MENU NHAN VIEN----------------\n";
	cout << "1. Hien thi danh sach nhan vien\n";
	cout << "2. Them nhan vien vao danh sach\n";
	cout << "3. Xoa nhan vien khoi danh sach\n";
	cout << "4. Sua nhan vien trong danh sach\n";
	cout << "5. Quay lai\n";
	cout << "----------------------------------------------\n";
	return 5;
}

int Choice(int max)
{
	int select;
	cout << "--> Nhap lua chon cua ban (1 <= lua chon <= " << max << "): ";
	cin >> select;
	while (cin.fail() || select<=0 || select>max)
	{
		cout << "-> Nhap sai lua chon!!! Xin moi nhap lai: ";
		cin.clear();
		cin.ignore();
		cin >> select;
	}
	return select;
}

void runStore(ProductList& prl, StaffList& stl, OrderList& odl)
{
	bool check, nonPause;
	int choice, select;
	char code[20];
	while (1)
	{
		system("cls");
		choice = Choice(storeMenu());
		system("cls");
		nonPause = false;
		switch (choice)
		{
		case 1:
			while (1)
			{
				system("cls");
				select = Choice(productMenu());
				system("cls");
				switch (select)
				{
				case 1:
					showProductList(prl);
					break;
				case 2:
					check = insertProduct(prl);
					if (!check)
						cout << "-> Ma san pham ban nhap da co san trong danh sach!!!" << endl;
					else
						cout << "-> Da them san pham moi vao danh sach" << endl;
					break;
				case 3:
					if (prl.list == NULL || prl.size == 0)
					{
						cout << "Danh sach san pham rong!!!" << endl;
						break;
					}
					cout << "- Nhap ma san pham muon xoa (dung 10 ki tu): ";
					cin.ignore();
					inputString(code, 10, Absolute);
					check = eraseProduct(prl, code);
					if (!check)
						cout << "-> Khong tim thay san pham voi ma vua nhap trong danh sach!!!" << endl;
					else
						cout << "-> Da xoa san pham voi ma vua nhap khoi danh sach" << endl;
					break;
				case 4:
					cout << "- Nhap ma san pham muon chinh sua (dung 10 ki tu): ";
					cin.ignore();
					inputString(code, 10, Absolute);
					editProduct(prl, code);
					break;
				default:
					nonPause = true;
					break;
				}
				if (!nonPause)
					system("pause");
				else
					break;
			}
			break;
		case 2:
			while (1)
			{
				system("cls");
				select = Choice(staffMenu());
				system("cls");
				switch (select)
				{
				case 1:
					showStaffList(stl);
					break;
				case 2:
					check = insertStaff(stl);
					if (!check)
						cout << "-> Ma nhan vien ban nhap da co san trong danh sach!!!" << endl;
					else
						cout << "-> Da them nhan vien moi vao danh sach" << endl;
					break;
				case 3:
					if (stl.list == NULL || stl.size == 0)
					{
						cout << "Danh sach nhan vien rong!!!" << endl;
						break;
					}
					cout << "- Nhap ma nhan vien muon xoa (dung 10 ki tu): ";
					cin.ignore();
					inputString(code, 10, Absolute);
					check = eraseStaff(stl, code);
					if (!check)
						cout << "-> Khong tim thay nhan vien voi ma vua nhap trong danh sach!!!" << endl;
					else
						cout << "-> Da xoa nhan vien voi ma vua nhap khoi danh sach" << endl;
					break;
				case 4:
					cout << "- Nhap ma nhan vien muon chinh sua (dung 10 ki tu): ";
					cin.ignore();
					inputString(code, 10, Absolute);
					editStaff(stl, code);
					break;
				default:
					nonPause = true;
					break;
				}
				if (!nonPause)
					system("pause");
				else
					break;
			}
			break;
		case 3:
			insertOrder(odl,prl);
			break;
		case 4:
			cout << "Nhap ngay de thong ke (dd/mm/yyyy): ";
			cin.ignore();
			inputDate(code);
			showListOrderWithDay(odl, code);
			break;
		default:
			return;
		}
		if(!nonPause)
			system("pause");
	}
}

void runProgram()
{
	ProductList prl;
	StaffList stl;
	OrderList odl;
	bool checkLogIn, check;
	int choice;
	loadProductList("dssp.bin", prl);
	loadStaffList("dsnv.bin", stl);
	loadOrderList("dsdh&dt.bin", odl);
	while (1)
	{
		system("cls");
		choice = Choice(mainMenu());
		system("cls");
		switch (choice)
		{
		case 1:
			cin.ignore();
			checkLogIn = logIn(stl);
			while (!checkLogIn)
			{
				gotoxy(40, 14);
				cout << "-> Dang nhap that bai!!!\n";
				gotoxy(40, 16);
				system("pause");
				system("cls");
				checkLogIn = logIn(stl);
			}
			runStore(prl, stl, odl);
			break;
		default:
			saveProductList("dssp.bin", prl);
			saveStaffList("dsnv.bin", stl);
			saveOrderList("dsdh&dt.bin", odl);
			destroyProductList(prl);
			destroyStaffList(stl);
			destroyOrderList(odl);
			exit(0);
		}
	}
}

