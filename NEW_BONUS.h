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
	char name[SHOP_NAME_SIZE] = "0";
	item items[SHOP_ITEMS_COUNT];
	int items_counter = 0;
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
	void add_item();
	void delete_item();
};

class promocode {
	item items[PROMOCODE_ITEM_SIZE];
	char code[CODE_SIZE] = "0";
	class expire {
		class date {
			int day = 0;
			int month = 0;
			int year = 0;
		};
		class timer {
			int second = 0;
			int minute = 0;
			int hour = 0;
		};
	};
	int items_counter = 0;
	int discount = 0;
};

class sale {
	item items[SALE_ITEMS_COUNT];
	char text[SALE_TEXT_LENGTH] = "0";
	int items_counter = 0;
};

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
