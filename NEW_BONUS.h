#pragma once
#include <vector>
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
	friend std::ostream& operator<<(std::ostream& os, const item& it);
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
	shop operator+ (shop& other);
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
	expire& operator++();
	expire operator++(int);
	friend std::ostream& operator<<(std::ostream& os, const expire& ex);
};

class promocode {
public:
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
	void init_add_item(item new_item);
	void delete_item(int item_number);
	int get_discount();
	void set_discount(int new_discount);
	int get_items_counter();
	void print() { std::cout << *this; }
	bool operator==(const promocode& rhs)
	{
		if (this->code == rhs.code) { return true; }
		else { return false; }
	}
	friend std::ostream& operator<<(std::ostream& os, const promocode& pr);
	friend bool operator <(const promocode& lhs, const promocode& rhs);
};

bool operator <(const promocode& lhs, const promocode& rhs) {
	if (lhs.discount != rhs.discount) { return lhs.discount < rhs.discount; }
	if (lhs.code != rhs.code) { return lhs.code < rhs.code; }
}

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
	friend std::ostream& operator<<(std::ostream& os, const sale& sa);
};

class expiring_promocode : public promocode {
public:
	expire this_expire;
public:
	expiring_promocode();
	expiring_promocode(std::string new_code);
	expiring_promocode(item new_items[], int new_items_counter, std::string new_code, expire new_expire, int new_discount);
	void get_expire(expire buffer);
	void set_expire(expire new_expire);
	void print_s_vizovom();
	void print_bez_vizova();
	expiring_promocode& operator=(const promocode& pr) {
		this->code = pr.code;
		//this->set_items(pr.items);
		this->items_counter = pr.items_counter;
		this->discount = pr.discount;
		this->set_expire(expire());
		return *this;
	};
	friend std::ostream& operator<<(std::ostream& os, const expiring_promocode& ex_pr);
};

template <typename T>
class person {
public:
	std::string name;
	int age;
	T id;
	person(std::string name, int age, T id);
	void get_name(std::string *name_buffer) { *name_buffer = name; }
	void set_name(std::string new_name) { name = new_name; }
	int get_age() { return age; }
	void set_age(int new_age) { age = new_age; }
	T get_id() { return id; }
	void set_id(T new_id) { id = new_id; }
	virtual void buy(item item_to_buy) = 0;
};

template <typename T>
person<T>::person(std::string new_name, int new_age, T new_id) {
	name = new_name; 
	age = new_age; 
	id = new_id;
}

template <typename T>
class customer : public person<T> {
	int money;
public:
	template <typename T>
	customer(std::string name, int age, T id, int money)
		: person<T>(name, age, id), money(money) {}
	int get_money() { return money; }
	void set_money(int new_money) { money = new_money; }
	void buy(item item_to_buy) override { money -= item_to_buy.get_price(); }
	friend std::ostream& operator<<(std::ostream& os, const customer<T>& cu) 
	{
		os << cu.name << " Имя " << cu.age << " Возраст " << cu.age << " ID " << cu.money << " Баланс\n";
		return os;
	};
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const customer<T>& cu) {}

std::ostream& operator<<(std::ostream& os, const item& it)
{
	os << it.name << " товар " << it.price << " цена " << it.discount << " скидка " << it.total_items_count << " всего товаров\n";
	return os;
}

std::ostream& operator<<(std::ostream& os, const shop& sh)
{
	os << sh.name << "\n";
	for (int i = 0; i < sh.items_counter; i++) {os << sh.items[i] << "\n"; } //?
	return os;
}

std::ostream& operator<<(std::ostream& os, const sale& sa)
{
	os << sa.text << "\n";
	for (int i = 0; i < sa.items_counter; i++) { os << sa.items[i] << "\n"; } //?
	return os;
}

std::ostream& operator<<(std::ostream& os, const expire& ex)
{
	os << ex.day << "/" << ex.month << "/" << ex.day << " " << ex.hour << ":" << ex.minute << ":" << ex.second;
	return os;
}

std::ostream& operator<<(std::ostream& os, const promocode& pr)
{
	os << pr.code << "\n";
	for (int i = 0; i < pr.items_counter; i++) { os << pr.items[i] << "\n"; } //?
	os << pr.discount << "\n";
	return os;
}

std::ostream& operator<<(std::ostream& os, const expiring_promocode& ex_pr)
{
	os << ex_pr.code << "\n";
	for (int i = 0; i < ex_pr.items_counter; i++) { os << ex_pr.items[i] << "\n"; } //?
	os << ex_pr.discount << "\n" << ex_pr.this_expire << "\n";
	return os;
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
	//if (this->name == "0" && name != "0") { total_items_count++; }
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

void promocode::init_add_item(item new_item) {
	std::string new_name;
	new_item.get_name(&new_name);
	promocode::items[promocode::items_counter].set_name(new_name);
	promocode::items[promocode::items_counter].set_price(new_item.get_price());
	promocode::items[promocode::items_counter].set_discount(new_item.get_discount());
}

promocode::promocode(item new_items[], int new_items_counter, std::string code, int new_discount) {
	for (int i = 0; i < new_items_counter; i++) {
		promocode::init_add_item(new_items[i]);
	}
	this->code = code;
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

void expiring_promocode::set_expire(expire new_expire) {
	this_expire.set_day(new_expire.get_day());
	this_expire.set_month(new_expire.get_month());
	this_expire.set_year(new_expire.get_year());
	this_expire.set_second(new_expire.get_second());
	this_expire.set_minute(new_expire.get_minute());
	this_expire.set_hour(new_expire.get_hour());
}

expiring_promocode::expiring_promocode(item new_items[], int new_items_counter, std::string new_code, expire new_expire, int new_discount) {
	this->items_counter = 0;
	for (int i = 0; i < new_items_counter; i++) {
		promocode::add_item(new_items[i]);
	}
	this->code = code;
	this_expire.set_day(new_expire.get_day());
	this_expire.set_month(new_expire.get_month());
	this_expire.set_year(new_expire.get_year());
	this_expire.set_second(new_expire.get_second());
	this_expire.set_minute(new_expire.get_minute());
	this_expire.set_hour(new_expire.get_hour());
	discount = new_discount;
}

expiring_promocode::expiring_promocode(std::string new_code) {
	items_counter = 0;
	discount = 0;
	this->code = new_code;
	set_expire(expire());//?
}

expiring_promocode::expiring_promocode() {
	items_counter = 0;
	discount = 0;
	code = "0";
	set_expire(expire());
}

void expiring_promocode::get_expire(expire buffer) {
	buffer.set_day(this_expire.get_day());
	buffer.set_month(this_expire.get_month());
	buffer.set_year(this_expire.get_year());
	buffer.set_second(this_expire.get_second());
	buffer.set_minute(this_expire.get_minute());
	buffer.set_hour(this_expire.get_hour());
}

void expiring_promocode::print_s_vizovom() {
	promocode::print();
	std::cout << this_expire;
}

void expiring_promocode::print_bez_vizova() {
	std::cout << *this;
}

