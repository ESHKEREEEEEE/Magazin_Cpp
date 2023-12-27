#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "NEW_BONUS.h"
#define SHOP_COUNT 30
#define SALE_COUNT 30
#define NAME_SIZE 30
#define TEXT_SIZE 30
#define ITEMS_COUNT 30
#define PROMOCODE_COUNT 30

int main()
{
    setlocale(LC_ALL, "Rus");
    promocode promocodes[PROMOCODE_COUNT];

    //тест методов item
    std::string name_for_item = "name";
    item new_item(name_for_item, 100, 0);
    new_item.print();
    std::string new_name = "new_name";
    new_item.set_name(new_name);
    new_item.set_price(228);
    new_item.set_discount(3);
    std::string string_buffer;
    new_item.get_name(&string_buffer);
    std::cout << string_buffer;
    printf(" %d %d \n", new_item.get_price(), new_item.get_discount());

    //тест методов shop
    shop new_shop;
    std::string name_for_shop = "name";
    new_shop.add_item(new_item);
    new_shop.set_name(name_for_shop);
    new_shop.print();
    item items_buffer[ITEMS_COUNT];
    new_shop.get_items(items_buffer);
    for (int i = 0; i < new_shop.get_items_counter(); i++) {
        items_buffer[i].print();
    }
    new_shop.delete_item(0);
    new_shop.get_name(&string_buffer);
    std::cout << string_buffer << "\n";
    new_shop.print();

    //тест методов sale
    std::string text_for_sale = "эх акция, акция\n";
    sale new_sale(text_for_sale);
    new_sale.get_text(&string_buffer);
    std::cout << string_buffer;
    new_sale.add_item(new_item);
    new_sale.get_items(items_buffer);
    for (int i = 0; i < new_sale.get_items_counter(); i++) {
        items_buffer[i].print();
    }
    string_buffer = "эщкере\n";
    new_sale.set_text(string_buffer);
    new_sale.delete_item(0);
    new_sale.print();

    //тест методов expire
    try {
        expire new_expire(16, 12, 2003, 22, 21, 20);
        printf("%d/%d/%d %d:%d:%d\n", new_expire.get_day(), new_expire.get_month(), new_expire.get_year(), new_expire.get_hour(), new_expire.get_minute(), new_expire.get_second());
        new_expire.set_day(10);
        new_expire.set_month(11);
        new_expire.set_year(12);
        new_expire.set_hour(13);
        new_expire.set_minute(14);
        new_expire.set_second(15);
        new_expire.print();
    

    //тест методов promocode
    promocode new_promocode;
    expire expire_buffer;
    std::string code_for_promocode = "mishkafreddy\n";
    new_promocode.set_code(code_for_promocode);
    new_promocode.get_code(&string_buffer);
    std::cout << string_buffer;
    new_promocode.add_item(new_item);
    new_promocode.get_items(items_buffer);
    for (int i = 0; i < new_promocode.get_items_counter(); i++) {
        items_buffer[i].print();
    }
    new_promocode.set_discount(10);
    printf("%d\n", new_promocode.get_discount());
    //new_promocode.set_expire(new_expire);
    //new_promocode.get_expire(expire_buffer);
    new_promocode.delete_item(0);
    new_promocode.print();

    //тест перегрузки операторов
    shop shop_to_plus;
    item first_item("bebra", 10, 1);
    item second_item("svo", 11, 2);
    shop first_shop("\nPudge", first_item);
    shop second_shop("Rudge", second_item);
    shop_to_plus = first_shop + second_shop;
    shop_to_plus.print();
    new_expire.print();
    new_expire++;
    new_expire.print();
    ++new_expire;
    new_expire.print();
    //тест передачи параметров по ссылке и через указатель
    printf("%d\n", *first_item.get_price_p());
    printf("%d\n", first_item.get_price_s());
    //двумерные массивы
    item item1("Эщ", 1, 1);
    item item2("ке", 2, 2);
    item item3("ре", 3, 3);
    item item4("0", 1, 1);
    item itemarr[2][2];
    itemarr[0][0] = item1;
    itemarr[0][1] = item2;
    itemarr[1][0] = item3;
    itemarr[1][1] = item4;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            try {
                itemarr[i][j].print();
            }
            catch (std::invalid_argument e) { std::cout << e.what();}
        }
    }
    }
    catch (std::invalid_argument e) { std::cout << e.what();}
    expiring_promocode().print_s_vizovom();
    expiring_promocode().print_bez_vizova();
    customer<int> abobus("azazaz", 12, 228, 10);
  
}