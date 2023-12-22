#pragma once
#include <iostream>
#include <string>
#include <stdexcept>
#define SHOP_NAME_SIZE 20
#define ITEM_NAME_SIZE 30
#define CODE_SIZE 30
#define SHOP_ITEMS_COUNT 30
#define SALE_ITEMS_COUNT 30
#define SALE_TEXT_LENGTH 100
#define PROMOCODE_ITEM_SIZE 30

class item {
	static int total_items_count;
	std::string name;
	int discount = 0;
	friend void item_deleted();
public:
	item();
	item(std::string new_name, int new_price, int new_discount);
	item(std::string new_name);
	void get_name(std::string *buffer);
	void set_name(std::string new_name);
	int get_price();
	int* get_price_p();
	int& get_price_s();
	void set_price(int new_price);
	int get_discount();
	void set_discount(int new_discount);
	void print();
	friend std::ostream& operator<<(std::ostream& os, const item& it);
	//item operator=(item it);
protected:
	int price = 0;
};

int item::total_items_count;

class shop {
	std::string name;
	item items[SHOP_ITEMS_COUNT];
	int items_counter;
public:
	shop();
	shop(std::string new_name, item new_item);
	shop(std::string new_name);
	void get_name(std::string *buffer);
	void set_name(std::string new_name);
	void get_items(item buffer[]);
	void add_item(item new_item);
	void delete_item(int item_number);
	int get_items_counter();
	void print();
	shop operator+ (shop& other);
	//shop operator=(shop sh);
	friend std::ostream& operator<<(std::ostream& os, const shop& sh);
};

class expire {
	int day;
	int month;
	int year;
	int second;
	int minute;
	int hour;
public:
	expire();
	expire(int new_day);
	expire(int new_day, int new_month, int new_year, int new_second, int new_minute, int new_hour);
	int get_day();
	int get_month();
	int get_year();
	int get_second();
	int get_minute();
	int get_hour();
	void set_day(int new_day);
	void set_month(int new_month);
	void set_year(int new_year);
	void set_second(int new_second);
	void set_minute(int new_minute);
	void set_hour(int new_hour);
	void print();
	expire& operator++();
	expire operator++(int);
	//expire operator=(expire ex);
	friend std::ostream& operator<<(std::ostream& os, const expire& ex);
};

class promocode {
	item items[PROMOCODE_ITEM_SIZE];
	std::string code;
	int items_counter;
	int discount;
public:
	promocode();
	promocode(std::string new_code);
	promocode(item new_items[], int new_items_counter, std::string new_code, int new_discount);
	void get_code(std::string *buffer);
	void set_code(std::string new_code);
	void get_items(item buffer[]);
	void set_items(item items_to_set[]);
	void add_item(item new_item);
	void delete_item(int item_number);
	int get_discount();
	void set_discount(int new_discount);
	int get_items_counter();
	void print();
	//promocode operator=(promocode pr);
	promocode operator=(expiring_promocode ex_pr);
	friend std::ostream& operator<<(std::ostream& os, const promocode& pr);
};

class sale {
	item items[SALE_ITEMS_COUNT];
	std::string text;
	int items_counter;
public:
	sale();
	sale(std::string new_text, item new_items[]);
	sale(std::string new_text);
	void get_text(std::string *buffer);
	void set_text(std::string new_text);
	void get_items(item buffer[]);
	void add_item(item new_item);
	void delete_item(int item_number);
	int get_items_counter();
	void print();
	//sale operator=(sale sa);
	friend std::ostream& operator<<(std::ostream& os, const sale& sa);
};

//производный класс + перегрузка метода базового класса
class expiring_promocode : public promocode {
	expire this_expire;
public:
	expiring_promocode();
	expiring_promocode(std::string new_code);
	expiring_promocode(item new_items[], int new_items_counter, std::string new_code, expire new_expire, int new_discount);
	void get_expire(expire buffer);
	void set_expire(expire new_expire);
	void print_s_vizovom();
	void print_bez_vizova();
	expiring_promocode operator=(promocode pr);
	friend std::ostream& operator<<(std::ostream& os, const expiring_promocode& ex_pr);
};

//абстрактный класс + шаблон класса
template <typename T>
class person {
	std::string name;
	int age;
	T id;
public:
	person(std::string name, int age, int id);
	void get_name(std::string name_buffer);
	void set_name(std::string new_name);
	int get_age();
	void set_age(int new_age);
	int get_id();
	void set_id(int new_id);
	virtual void buy(item item_to_buy) = 0;
	person operator=(person pe);
	friend std::ostream& operator<<(std::ostream& os, const person& pe);
};

template <typename T>
class customer : public person<T> {
	int money;
public:
	customer(std::string name, int age, int id, int money); //вызвать базовый конструктор
	int get_money();
	void set_money(int new_money);
	void buy();
	customer operator=(customer cu);
	friend std::ostream& operator<<(std::ostream& os, const customer& cu);
};

std::ostream& operator<<(std::ostream& os, const item& it)
{
	os << it.name << " товар " << it.price << " цена " << it.discount << " скидка " << it.total_items_count << " всего товаров\n";
	return os;
}

expiring_promocode expiring_promocode::operator=(promocode pr){
	item items_buffer[SHOP_ITEMS_COUNT];
	std::string code_buffer;
	int items_counter_buffer;
	int discount_buffer;
	pr.get_items(items_buffer);
	pr.get_code(&code_buffer);
	items_counter_buffer = pr.get_items_counter(); //возможно убрать
	discount_buffer = pr.get_discount();
	set_items(items_buffer);
	set_code(code_buffer);
	set_discount(discount_buffer);
	set_expire(expire()); //?
}

void itemcpy(item destination, item source) {
	std::string source_name;
	source.get_name(&source_name);
	destination.set_name(source_name);
	destination.set_discount(source.get_discount());
	destination.set_price(source.get_price());
}

void item_deleted() {
	item::total_items_count--;
}


shop shop::operator+(shop& other) {
	shop new_shop;
	std::string buffer1;
	std::string buffer2;
	this->get_name(&buffer1);
	other.get_name(&buffer2);
	std::string new_name = buffer1 + buffer2;
	new_shop.set_name(new_name);
	for (int i = 0; i < this->items_counter; i++) {
		new_shop.add_item(this->items[i]);
	}
	for (int i = 0; i < other.items_counter; i++) {
		new_shop.add_item(other.items[i]);
	}
	return new_shop;
}

expire& expire::operator++() {
	second++;
	return *this;
}

expire expire::operator++(int) {
	expire temp = *this;
	++*this;
	return temp;
}

item::item() {
	this->name = "0";
	price = 0;
	discount = 0;
}

item::item(std::string name, int price, int discount) {
	this->name = name;
	this->price = price;
	this->discount = discount;
	if (this->name != "0") { total_items_count++; }
}

item::item(std::string name) {
	this->name = name;
	price = 0;
	discount = 0;
	if (this->name != "0") { total_items_count++; }
}

void item::get_name(std::string *buffer) {
	*(buffer) = this->name;
}

void item::set_name(std::string name) {
	if (this->name == "0" && name != "0") { total_items_count++; }
	this->name = name;
}

int item::get_price(){
	return item::price;
}

int* item::get_price_p() {
	int* p = &this->price;
	return p;
}

int& item::get_price_s() {
	return  this->price;
}

void item::set_price(int new_price) {
	item::price = new_price;
}

int item::get_discount() {
	return item::discount;
}

void item::set_discount(int new_discount) {
	item::discount = new_discount;
}

void item::print() {
	if (this->name != "0") { std::cout << item::name << " товар " << item::price << " цена " << item::discount << " скидка " << item::total_items_count << " всего товаров\n"; }
	else if (this->price != 0 and this->discount != 0) throw std::invalid_argument("NO ITEM NAME BUT PRICE AND DISCOUNT != 0");
}

shop::shop() {
	this->name = "0";
	items_counter = 0;
}

void shop::add_item(item new_item) {
	std::string new_name;
	new_item.get_name(&new_name);
	shop::items[shop::items_counter].set_name(new_name);
	shop::items[shop::items_counter].set_price(new_item.get_price());
	shop::items[shop::items_counter].set_discount(new_item.get_discount());
	shop::items_counter++;
}

shop::shop(std::string name, item new_item) {
	items_counter = 0;
	this->name = name;
	add_item(new_item);
}

shop::shop(std::string new_name) {
	items_counter = 0;
	this->name = new_name;
}

void shop::get_name(std::string *buffer) {
	*(buffer) = this->name;
}

void shop::set_name(std::string name) {
	this->name = name;
}

void shop::get_items(item buffer[]) {
	for (int i = 0; i < items_counter; i++) {
		itemcpy(buffer[i], items[i]);
	}
}

void shop::delete_item(int item_number) {
	shop::items[item_number].set_name("0");
	shop::items[item_number].set_price(0);
	shop::items[item_number].set_discount(0);
	items_counter--;
	item_deleted();
}

int shop::get_items_counter() {
	return items_counter;
}

void shop::print() {
	std::cout << this->name << "\n";
	for (int i = 0; i < items_counter; i++) {
		shop::items[i].print();
	}
}

expire::expire() {
	day = 0;
	month = 0;
	year = 0;
	second = 0;
	minute = 0;
	hour = 0;
}

expire::expire(int new_day) {
	day = new_day;
	month = 0;
	year = 0;
	second = 0;
	minute = 0;
	hour = 0;
	if (day < 0 or day > 31) { throw std::invalid_argument("Day needs to be less than 31 and more than 0"); }
}

expire::expire(int new_day, int new_month, int new_year, int new_second, int new_minute, int new_hour) {
	day = new_day;
	month = new_month;
	year = new_year;
	second = new_second;
	minute = new_minute;
	hour = new_hour;
	if (day < 0 or day > 31) { throw std::invalid_argument("Day needs to be less than 31 and more than 0"); }
	if (month < 0 or month > 12) { throw std::invalid_argument("Month needs to be less than 12 and more than 0"); }
	if (second < 0 or second > 23) { throw std::invalid_argument("Hour needs to be less than 23 and more than 0"); }
	if (minute < 0 or minute > 59) { throw std::invalid_argument("Minute needs to be less than 59 and more than 0"); }
	if (hour < 0 or hour > 59) { throw std::invalid_argument("Second needs to be less than 59 and more than 0"); }
}

int expire::get_day() {
	return day;
}

int expire::get_month() {
	return month;
}

int expire::get_year() {
	return year;
}

int expire::get_second() {
	return second;
}

int expire::get_minute() {
	return minute;
}

int expire::get_hour() {
	return hour;
}

void expire::set_day(int new_day) {
	day = new_day;
	if (day < 0 or day > 31) { throw std::invalid_argument("Day needs to be less than 31 and more than 0"); }
}

void expire::set_month(int new_month) {
	month = new_month;
	if (month < 0 or month > 12) { throw std::invalid_argument("Month needs to be less than 12 and more than 0"); }
}

void expire::set_year(int new_year) {
	year = new_year;
}

void expire::set_second(int new_second) {
	second = new_second;
	if (second < 0 or second > 23) { throw std::invalid_argument("Hour needs to be less than 23 and more than 0"); }
}

void expire::set_minute(int new_minute) {
	minute = new_minute;
	if (minute < 0 or minute > 59) { throw std::invalid_argument("Minute needs to be less than 59 and more than 0"); }
}

void expire::set_hour(int new_hour) {
	hour = new_hour;
	if (hour < 0 or hour > 59) { throw std::invalid_argument("Second needs to be less than 59 and more than 0"); }
}

void expire::print() {
	printf("%d/%d/%d %d:%d:%d\n", day, month, year, hour, minute, second);
}

void promocode::set_discount(int new_discount) {
	promocode::discount = new_discount;
}

int promocode::get_items_counter() {
	return promocode::items_counter;
}

promocode::promocode() {
	this->code = "0";
	items_counter = 0;
	discount = 0;
}

promocode::promocode(std::string code) {
	this->code = code;
	items_counter = 0;
	discount = 0;
}

void promocode::add_item(item new_item) {
	std::string new_name;
	new_item.get_name(&new_name);
	promocode::items[promocode::items_counter].set_name(new_name);
	promocode::items[promocode::items_counter].set_price(new_item.get_price());
	promocode::items[promocode::items_counter].set_discount(new_item.get_discount());
	promocode::items_counter++;
}

promocode::promocode(item new_items[], int new_items_counter, std::string code, int new_discount) {
	for (int i = 0; i < new_items_counter; i++) {
		promocode::add_item(new_items[i]);
	}
	this->code = code;
	//this_expire.set_day(new_expire.get_day());
	//this_expire.set_month(new_expire.get_month());
	//this_expire.set_year(new_expire.get_year());
	//this_expire.set_second(new_expire.get_second());
	//this_expire.set_minute(new_expire.get_minute());
	//this_expire.set_hour(new_expire.get_hour());
	discount = new_discount;
}

void promocode::get_code(std::string *buffer) {
	*(buffer) = this->code;
}

void promocode::set_code(std::string code) {
	this->code = code;
}

void promocode::get_items(item buffer[]) {
	for (int i = 0; i < items_counter; i++) {
		itemcpy(buffer[i], items[i]);
	}
}

void promocode::set_items(item items_to_set[]) {
	for (int i = 0; i < items_counter; i++) {
		this->add_item(items_to_set[i]);
	}
}

void promocode::delete_item(int item_number) {
	promocode::items[item_number].set_name("0");
	promocode::items[item_number].set_price(0);
	promocode::items[item_number].set_discount(0);
	items_counter--;
	item_deleted();
}

int promocode::get_discount() {
	return discount;
}

/*void promocode::get_expire(expire buffer) {
	buffer.set_day(this_expire.get_day());
	buffer.set_month(this_expire.get_month());
	buffer.set_year(this_expire.get_year());
	buffer.set_second(this_expire.get_second());
	buffer.set_minute(this_expire.get_minute());
	buffer.set_hour(this_expire.get_hour());
}

void promocode::set_expire(expire new_expire) {
	this_expire.set_day(new_expire.get_day());
	this_expire.set_month(new_expire.get_month());
	this_expire.set_year(new_expire.get_year());
	this_expire.set_second(new_expire.get_second());
	this_expire.set_minute(new_expire.get_minute());
	this_expire.set_hour(new_expire.get_hour());
}*/

void promocode::print() {
	std::cout << this->code;
	for (int i = 0; i < items_counter; i++) {
		items[i].print();
	}
	//this_expire.print();
	printf("Скидка %d", discount);
}

void sale::add_item(item new_item) {
	std::string new_name;
	new_item.get_name(&new_name);
	sale::items[sale::items_counter].set_name(new_name);
	sale::items[sale::items_counter].set_price(new_item.get_price());
	sale::items[sale::items_counter].set_discount(new_item.get_discount());
	sale::items_counter++;
}

sale::sale() {
	text = "0";
	items_counter = 0;
}

sale::sale(std::string text, item new_items[]) {
	items_counter = 0;
	this->text = text;
	for (int i = 0; i < items_counter; i++) {
		add_item(new_items[i]);
	}
}

sale::sale(std::string text) {
	this->text = text;
	items_counter = 0;
}

void sale::get_text(std::string *buffer) {
	*(buffer) = this->text;
}

void sale::set_text(std::string text) {
	this->text = text;
}

void sale::get_items(item buffer[]) {
	for (int i = 0; i < items_counter; i++) {
		itemcpy(buffer[i], items[i]);
	}
}

void sale::delete_item(int item_number) {
	sale::items[item_number].set_name("0");
	sale::items[item_number].set_price(0);
	sale::items[item_number].set_discount(0);
	items_counter--;
	item_deleted();
}

int sale::get_items_counter() {
	return items_counter;
}

void sale::print() {
	std::cout << text;
	for (int i = 0; i < items_counter; i++) {
		items[i].print();
	}
}