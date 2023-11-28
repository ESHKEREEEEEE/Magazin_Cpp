#pragma once
#include <iostream>
#include <string>
#define SHOP_NAME_SIZE 20
#define ITEM_NAME_SIZE 30
#define CODE_SIZE 30
#define SHOP_ITEMS_COUNT 30
#define SALE_ITEMS_COUNT 30
#define SALE_TEXT_LENGTH 100
#define PROMOCODE_ITEM_SIZE 30

class item {
	std::string name;
	int price = 0;
	int discount = 0;
public:
	item();
	item(std::string new_name, int new_price, int new_discount);
	item(std::string new_name);
	void get_name(std::string buffer);
	void set_name(std::string new_name);
	int get_price();
	void set_price(int new_price);
	int get_discount();
	void set_discount(int new_discount);
	void print();
};

class shop {
	std::string name;
	item items[SHOP_ITEMS_COUNT];
	int items_counter;
public:
	shop();
	shop(std::string new_name, item new_item);
	shop(std::string new_name);
	void get_name(std::string buffer);
	void set_name(std::string new_name);
	void get_items(item buffer[]);
	void add_item(item new_item);
	void delete_item(int item_number);
	int get_items_counter();
	void print();
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
};

class promocode {
	item items[PROMOCODE_ITEM_SIZE];
	std::string code;
	expire this_expire;
	int items_counter;
	int discount;
public:
	promocode();
	promocode(std::string new_code);
	promocode(item new_items[], int new_items_counter, std::string new_code, expire new_expire, int new_discount);
	void get_code(std::string buffer);
	void set_code(std::string new_code);
	void get_items(item buffer[]);
	void add_item(item new_item);
	void delete_item(int item_number);
	int get_discount();
	void set_discount(int new_discount);
	int get_items_counter();
	void get_expire(expire buffer);
	void set_expire(expire new_expire);
	void print();
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
};

void itemcpy(item destination, item source) {
	std::string source_name;
	source.get_name(source_name);
	destination.set_name(source_name);
	destination.set_discount(source.get_discount());
	destination.set_price(source.get_price());
}

item::item() {
	this->name = "0";
	price = 0;
	discount = 0;
}

item::item(std::string new_name, int new_price, int new_discount) {
	this->name = new_name;
	price = new_price;
	discount = new_discount;
}

item::item(std::string new_name) {
	this->name = new_name;
	price = 0;
	discount = 0;
}

void item::get_name(std::string buffer) {
	buffer = this->name;
}

void item::set_name(std::string new_name) {
	this->name = new_name;
}

int item::get_price(){
	return item::price;
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
	printf("%s товар %d цена %d скидка\n",item::name, item::price, item::discount);
}

shop::shop() {
	this->name = "0";
	items_counter = 0;
}

void shop::add_item(item new_item) {
	std::string new_name;
	new_item.get_name(new_name);
	shop::items[shop::items_counter].set_name(new_name);
	shop::items[shop::items_counter].set_price(new_item.get_price());
	shop::items[shop::items_counter].set_discount(new_item.get_discount());
	shop::items_counter++;
}

shop::shop(std::string new_name, item new_item) {
	items_counter = 0;
	this->name = new_name;
	add_item(new_item);
}

shop::shop(std::string new_name) {
	items_counter = 0;
	this->name = new_name;
}

void shop::get_name(std::string buffer) {
	buffer = this->name;
}

void shop::set_name(std::string new_name) {
	this->name = new_name;
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
}

int shop::get_items_counter() {
	return items_counter;
}

void shop::print() {
	std::cout << this->name;
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
}

expire::expire(int new_day, int new_month, int new_year, int new_second, int new_minute, int new_hour) {
	day = new_day;
	month = new_month;
	year = new_year;
	second = new_second;
	minute = new_minute;
	hour = new_hour;
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
}

void expire::set_month(int new_month) {
	month = new_month;
}

void expire::set_year(int new_year) {
	year = new_year;
}

void expire::set_second(int new_second) {
	second = new_second;
}

void expire::set_minute(int new_minute) {
	minute = new_minute;
}

void expire::set_hour(int new_hour) {
	hour = new_hour;
}

void expire::print() {
	printf("%d/%d/%d %d:%d:%d\n", day, month, year, second, minute, hour);
}

//ghfhfgd
void promocode::set_discount(int new_discount) {
	promocode::discount = new_discount;
}

int promocode::get_items_counter() {
	return promocode::items_counter;
}
//vghdhhhxtbj

promocode::promocode() {
	this->code = "0";
	items_counter = 0;
	discount = 0;
}

promocode::promocode(std::string new_code) {
	this->code = new_code;
	items_counter = 0;
	discount = 0;
}

void promocode::add_item(item new_item) {
	std::string new_name;
	new_item.get_name(new_name);
	promocode::items[promocode::items_counter].set_name(new_name);
	promocode::items[promocode::items_counter].set_price(new_item.get_price());
	promocode::items[promocode::items_counter].set_discount(new_item.get_discount());
	promocode::items_counter++;
}

promocode::promocode(item new_items[], int new_items_counter, std::string new_code, expire new_expire, int new_discount) {
	for (int i = 0; i < new_items_counter; i++) {
		promocode::add_item(new_items[i]);
	}
	this->code = new_code;
	this_expire.set_day(new_expire.get_day());
	this_expire.set_month(new_expire.get_month());
	this_expire.set_year(new_expire.get_year());
	this_expire.set_second(new_expire.get_second());
	this_expire.set_minute(new_expire.get_minute());
	this_expire.set_hour(new_expire.get_hour());
	discount = new_discount;
}

void promocode::get_code(std::string buffer) {
	buffer = this->code;
}

void promocode::set_code(std::string new_code) {
	this->code = new_code;
}

void promocode::get_items(item buffer[]) {
	for (int i = 0; i < items_counter; i++) {
		itemcpy(buffer[i], items[i]);
	}
}

void promocode::delete_item(int item_number) {
	promocode::items[item_number].set_name("0");
	promocode::items[item_number].set_price(0);
	promocode::items[item_number].set_discount(0);
	items_counter--;
}

int promocode::get_discount() {
	return discount;
}

void promocode::get_expire(expire buffer) {
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
}

void promocode::print() {
	std::cout << this->code;
	for (int i = 0; i < items_counter; i++) {
		items[i].print();
	}
	this_expire.print();
	printf("Скидка %d", discount);
}

void sale::add_item(item new_item) {
	std::string new_name;
	new_item.get_name(new_name);
	sale::items[sale::items_counter].set_name(new_name);
	sale::items[sale::items_counter].set_price(new_item.get_price());
	sale::items[sale::items_counter].set_discount(new_item.get_discount());
	sale::items_counter++;
}

sale::sale() {
	text = "0";
	items_counter = 0;
}

sale::sale(std::string new_text, item new_items[]) {
	items_counter = 0;
	this->text = new_text;
	for (int i = 0; i < items_counter; i++) {
		add_item(new_items[i]);
	}
}

sale::sale(std::string new_text) {
	this->text = new_text;
	items_counter = 0;
}

void sale::get_text(std::string *buffer) {
	*(buffer) = this->text;
}

void sale::set_text(std::string new_text) {
	this->text = new_text;
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