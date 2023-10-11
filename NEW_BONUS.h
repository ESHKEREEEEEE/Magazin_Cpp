#pragma once
#define SHOP_NAME_SIZE 20
#define ITEM_NAME_SIZE 30
#define CODE_SIZE 30
#define SHOP_ITEMS_COUNT 30
#define SALE_ITEMS_COUNT 30
#define SALE_TEXT_LENGTH 100
#define PROMOCODE_ITEM_SIZE 30

class item {
	char name[ITEM_NAME_SIZE] = "0";
	int price = 0;
	int discount = 0;
public:
	item();
	item(char new_name[], int new_price, int new_discount);
	item(char new_name[]);
	void get_name(char buffer[]);
	void set_name(char new_name[]);
	int get_price();
	void set_price(int new_price);
	int get_discount();
	void set_discount(int new_discount);
	void print();
};

class shop {
	char name[SHOP_NAME_SIZE];
	item items[SHOP_ITEMS_COUNT];
	int items_counter;
public:
	shop();
	shop(char new_name[], item new_item);
	shop(char new_name[]);
	void get_name(char buffer[]);
	void set_name(char new_name[]);
	void get_items(item buffer[]);
	void add_item(item new_item);
	void delete_item(int item_number);
	int get_items_counter();
	void print();
};

class promocode {
	item items[PROMOCODE_ITEM_SIZE];
	char code[CODE_SIZE] = "0";
	class expire {
		class date {
			int day = 0;
			int month = 0;
			int year = 0;
		public:
			date();
			date(int day);
			date(int day, int month, int year);
			int get_day();
			int get_month();
			int get_year();
			void set_day(int new_day);
			void set_month(int new_month);
			void set_year(int new_year);
		};
		class timer {
			int second = 0;
			int minute = 0;
			int hour = 0;
		public:
			timer();
			timer(int second);
			timer(int second, int minute, int hour);
			int get_day();
			int get_month();
			int get_year();
			void set_day(int new_second);
			void set_month(int new_minute);
			void set_year(int new_hour);
		};
	public:
		expire();
		expire(date new_date, timer new_timer);
	};
	int items_counter = 0;
	int discount = 0;
public:
	promocode();
	promocode(char new_code[]);
	promocode(item new_items[], char new_code[], expire new_expire, int new_discount);
	void get_code(char buffer[]);
	void set_code(char new_code[]);
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
	char text[SALE_TEXT_LENGTH] = "0";
	int items_counter = 0;
public:
	sale();
	sale(char new_text[], item new_item);
	sale(char new_text[]);
	void get_text(char buffer[]);
	void set_text(char new_name[]);
	void get_items(item buffer[]);
	void add_item(item new_item);
	void delete_item(int item_number);
	int get_items_counter();
	void print();
};

void itemcpy(item destination, item source) {
	char source_name;
	source.get_name(&source_name);
	destination.set_name(&source_name);
	destination.set_discount(source.get_discount());
	destination.set_price(source.get_price());
}

item::item() {
	strcpy(name, "0");
	price = 0;
	discount = 0;
}

item::item(char new_name[], int new_price, int new_discount) {
	strcpy(name, new_name);
	price = new_price;
	discount = new_discount;
}

item::item(char new_name[]) {
	strcpy(name, new_name);
}

void item::get_name(char buffer[]) {
	strcpy(buffer, name);
}

void item::set_name(char new_name[]) {
	strcpy(item::name, new_name);
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
	printf("%s товар %d цена %d скидка",item::name, item::price, item::discount);
}

shop::shop() {
	strcpy(name, "0");
	items_counter = 0;
}

void shop::add_item(item new_item) {
	char new_name[ITEM_NAME_SIZE];
	new_item.get_name(new_name);
	shop::items[shop::items_counter].set_name(new_name);
	shop::items[shop::items_counter].set_price(new_item.get_price());
	shop::items[shop::items_counter].set_discount(new_item.get_discount());
	shop::items_counter++;
}

shop::shop(char new_name[], item new_item) {
	items_counter = 0;
	strcpy(name, new_name);
	add_item(new_item);
}

shop::shop(char new_name[]) {
	items_counter = 0;
	strcpy(name, new_name);
}

void shop::get_name(char buffer[]) {
	strcpy(buffer, name);
}

void shop::set_name(char new_name[]) {
	strcpy(name, new_name);
}

void shop::get_items(item buffer[]) {
	for (int i = 0; i < items_counter; i++) {
		itemcpy(buffer[i], items[i]);
	}
}

void shop::delete_item(int item_number) {
	char null_name = '0';
	shop::items[item_number].set_name(&null_name);
	shop::items[item_number].set_price(0);
	shop::items[item_number].set_discount(0);
	items_counter--;
}

int shop::get_items_counter() {
	return items_counter;
}

void shop::print() {
	puts(name);
	for (int i = 0; i < items_counter; i++) {
		shop::items[i].print();
	}
}