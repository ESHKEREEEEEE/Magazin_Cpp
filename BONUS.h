#pragma once
#define SHOP_NAME_SIZE 20
#define ITEM_NAME_SIZE 30
#define CODE_SIZE 30
#define SHOP_ITEMS_COUNT 30
#define SALE_ITEMS_COUNT 30
#define SALE_TEXT_LENGTH 100
#define PROMOCODE_ITEM_SIZE 30

struct item {
	char name[ITEM_NAME_SIZE] = "0";
	int price = 0;
	int discount = 0;
};

struct shop {
	char name[SHOP_NAME_SIZE] = "0";
	item items[SHOP_ITEMS_COUNT];
	int items_counter = 0;
};


struct date {
	int day = 0;
	int month = 0;
	int year = 0;
};

struct timer {
	int second = 0;
	int minute = 0;
	int hour = 0;
};

struct expire {
	date date;
	timer time;
};


struct promocode {
	item items[PROMOCODE_ITEM_SIZE];
	char code[CODE_SIZE] = "0";
	expire expire;
	int items_counter = 0;
	int discount = 0;
};

struct sale {
	item items[SALE_ITEMS_COUNT];
	char text[SALE_TEXT_LENGTH] = "0";
	int items_counter = 0;
};

void create_shop(shop* shop_cr) {
	char shop_name[SHOP_NAME_SIZE];
	printf("Введите название магазина ");
	gets_s(shop_name, SHOP_NAME_SIZE);
	*shop_cr->name = *shop_name;
	printf("Создан магазин %s\n", shop_name);
}

void add_item(shop* add_item) {
	char item_name[ITEM_NAME_SIZE];
	int item_price, item_discount;
	printf("Введите название товара ");
	gets_s(item_name, ITEM_NAME_SIZE);
	strcpy((add_item->items[add_item->items_counter].name), item_name);
	printf("Введите цену товара ");
	scanf("%d", &item_price);
	add_item->items[add_item->items_counter].price = item_price;
	printf("Введите скидку ");
	scanf("%d", &item_discount);
	add_item->items[add_item->items_counter].discount = item_discount;
	printf("Добавлен товар %s по цене %d со скидкой %d\n", item_name, item_price, item_discount);
	add_item->items_counter++;
	while (getchar() != '\n');
}

void add_item(promocode* add_item) {
	char item_name[ITEM_NAME_SIZE];
	int item_price, item_discount;
	printf("Введите название товара ");
	gets_s(item_name, ITEM_NAME_SIZE);
	strcpy((add_item->items[add_item->items_counter].name), item_name);
	printf("Введите цену товара ");
	scanf("%d", &item_price);
	add_item->items[add_item->items_counter].price = item_price;
	printf("Введите скидку ");
	scanf("%d", &item_discount);
	add_item->items[add_item->items_counter].discount = item_discount;
	printf("Добавлен товар %s по цене %d со скидкой %d\n", item_name, item_price, item_discount);
	add_item->items_counter++;
	while (getchar() != '\n');
}

void add_item(sale* add_item) {
	char item_name[ITEM_NAME_SIZE];
	int item_price, item_discount;
	printf("Введите название товара ");
	gets_s(item_name, ITEM_NAME_SIZE);
	strcpy((add_item->items[add_item->items_counter].name), item_name);
	printf("Введите цену товара ");
	scanf("%d", &item_price);
	add_item->items[add_item->items_counter].price = item_price;
	printf("Введите скидку ");
	scanf("%d", &item_discount);
	add_item->items[add_item->items_counter].discount = item_discount;
	printf("Добавлен товар %s по цене %d со скидкой %d\n", item_name, item_price, item_discount);
	add_item->items_counter++;
	while (getchar() != '\n');
}

void item_info(item* current_item) {
	char current_item_name[ITEM_NAME_SIZE];
	strcpy(current_item_name,  current_item->name);
	printf("%s по цене %d со скидкой %d \n", current_item_name, current_item->price, current_item->discount);
}

void shop_info(shop* current_shop) {
	printf("%s\n", *(current_shop->name));
	for (int i = 0; i < current_shop->items_counter; i++) {
		item_info(&current_shop->items[i]);
	}
}

void change_item_name(item* current_item){
	char item_name[ITEM_NAME_SIZE];
	printf("Введите название товара ");
	gets_s(item_name, ITEM_NAME_SIZE);
	*current_item->name = *item_name;
}

void change_item_price(item* current_item) {
	int item_price;
	printf("Введите цену товара ");
	scanf("%d", &item_price);
	current_item->price = item_price;
	while (getchar() != '\n');
}

void change_item_discount(item* current_item) {
	int item_discount;
	printf("Введите скидку на товар ");
	scanf("%d", &item_discount);
	current_item->price = item_discount;
	while (getchar() != '\n');
}

void delete_item(shop* shop_delete_item, int item_to_delete) {
	*shop_delete_item->items[item_to_delete].name = *("0");
	shop_delete_item->items[item_to_delete].price = 0;
	shop_delete_item->items[item_to_delete].discount = 0;
	shop_delete_item->items_counter--;
}

void delete_item(sale* sale_delete_item, int item_to_delete) {
	*sale_delete_item->items[item_to_delete].name = *("0");
	sale_delete_item->items[item_to_delete].price = 0;
	sale_delete_item->items[item_to_delete].discount = 0;
	sale_delete_item->items_counter--;
}

void delete_item(promocode* promocode_delete_item, int item_to_delete) {
	*promocode_delete_item->items[item_to_delete].name = *("0");
	promocode_delete_item->items[item_to_delete].price = 0;
	promocode_delete_item->items[item_to_delete].discount = 0;
	promocode_delete_item->items_counter--;
}

void change_date_day(date* date_to_change) {
	int new_day;
	printf("Введите день ");
	scanf("%d", &new_day);
	date_to_change->day = new_day;
	while (getchar() != '\n');
}

void change_date_month(date* date_to_change) {
	int new_month;
	printf("Введите месяц ");
	scanf("%d", &new_month);
	date_to_change->month = new_month;
	while (getchar() != '\n');
}

void change_date_year(date* date_to_change) {
	int new_year;
	printf("Введите год ");
	scanf("%d", &new_year);
	date_to_change->year = new_year;
	while (getchar() != '\n');
}

void change_time_hour(timer* time_to_change) {
	int new_hour;
	printf("Введите час ");
	scanf("%d", &new_hour);
	time_to_change->hour = new_hour;
	while (getchar() != '\n');
}

void change_time_minute(timer* time_to_change) {
	int new_minute;
	printf("Введите минуту ");
	scanf("%d", &new_minute);
	time_to_change->minute = new_minute;
	while (getchar() != '\n');
}

void change_time_second(timer* time_to_change) {
	int new_second;
	printf("Введите секунду ");
	scanf("%d", &new_second);
	time_to_change->second = new_second;
	while (getchar() != '\n');
}

void create_promocode(promocode* promocode_cr) {
	char promocode[CODE_SIZE];
	int discount;
	printf("Введите промокод ");
	gets_s(promocode, CODE_SIZE);
	//*promocode_cr->code = *promocode;
	strcpy(promocode_cr->code, promocode);
	change_date_day(&(promocode_cr->expire.date));
	change_date_month(&(promocode_cr->expire.date));
	change_date_year(&(promocode_cr->expire.date));
	change_time_second(&(promocode_cr->expire.time));
	change_time_minute(&(promocode_cr->expire.time));
	change_time_hour(&(promocode_cr->expire.time));
	printf("Введите скидку ");
	scanf("%d", &discount);
	promocode_cr->discount = discount;
	while (getchar() != '\n');
}

void promocode_info(promocode* current_promocode) {
	char current_promocode_code[CODE_SIZE];
	strcpy(current_promocode_code, current_promocode->code);
	puts(current_promocode_code);
	for (int i = 0; i < current_promocode->items_counter; i++) {
		item_info(&(current_promocode->items[i]));
	}
	printf("Код истечет в %d:%d:%d %d/%d/%d \n", current_promocode->expire.time.hour, current_promocode->expire.time.minute, current_promocode->expire.time.second, current_promocode->expire.date.day, current_promocode->expire.date.month, current_promocode->expire.date.year);
}

void create_sale(sale* sale_cr) {
	char sale_text[SALE_TEXT_LENGTH];
	printf("Введите условия акции ");
	gets_s(sale_text, SALE_TEXT_LENGTH);
	strcpy(sale_cr->text, sale_text);
	//*sale_cr->text = *sale_text;
}

void change_sale_text(sale* sale_to_change) {
	char sale_text[SALE_TEXT_LENGTH];
	printf("Введите условия акции ");
	gets_s(sale_text, SALE_TEXT_LENGTH);
	strcpy(sale_to_change->text, sale_text);
	//*sale_to_change->text = *sale_text;
}

void sale_info(sale* current_sale) {
	//printf("%s\n", *(current_sale->text));
	puts(current_sale->text);
	for (int i = 0; i < current_sale->items_counter; i++) {
		item_info(&current_sale->items[i]);
	}
}

void delete_sale(sale* sale_to_delete) {
	int current_item_to_delete = sale_to_delete->items_counter;
	*sale_to_delete->text = *"0";
	while (sale_to_delete->items_counter > 0) {
		delete_item(sale_to_delete, current_item_to_delete);
		current_item_to_delete--;
	}
}

void change_promocode_code(promocode* promocode_to_change) {
	printf("Введите новый код ");
	char new_code[CODE_SIZE];
	gets_s(new_code, CODE_SIZE);
	*promocode_to_change->code = *new_code;
}

void change_promocode_discount(promocode* promocode_to_change) {
	printf("Введите новую скидку ");
	int new_discount;
	scanf("%d", &new_discount);
	promocode_to_change->discount = new_discount;
	while (getchar() != '\n');
}

void delete_promocode(promocode* promocode_to_delete) {
	int current_item_to_delete = promocode_to_delete->items_counter;
	*promocode_to_delete->code = *"0";
	while (promocode_to_delete->items_counter > 0) {
		delete_item(promocode_to_delete, current_item_to_delete);
		current_item_to_delete--;
	}
	promocode_to_delete->discount = 0;
	promocode_to_delete->expire.date.day = 0;
	promocode_to_delete->expire.date.month = 0;
	promocode_to_delete->expire.date.year = 0;
	promocode_to_delete->expire.time.hour = 0;
	promocode_to_delete->expire.time.minute = 0;
	promocode_to_delete->expire.time.second = 0;
}

void delete_shop(shop* shop_to_delete) {
	int current_item_to_delete = shop_to_delete->items_counter;
	*shop_to_delete->name = *"0";
	while (shop_to_delete->items_counter > 0) {
		delete_item(shop_to_delete, current_item_to_delete);
		current_item_to_delete--;
	}
}