#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>

struct Person {
    std::string name;
    std::string phone;
};

class PhoneBook {
private:
    std::vector<Person> contacts;
    const std::string filename = "phonebook.txt";

    void loadFromFile() {
        std::ifstream file(filename);
        if (file.is_open()) {
            std::string name, phone;
            while (file >> name >> phone) {
                contacts.push_back({name, phone});
            }
            file.close();
        }
    }

    void saveToFile() {
        std::ofstream file(filename);
        if (file.is_open()) {
            for (const auto& contact : contacts) {
                file << contact.name << " " << contact.phone << "\n";
            }
            file.close();
        }
    }

public:
    PhoneBook() {
        loadFromFile();
    }

    ~PhoneBook() {
        saveToFile();
    }

    void addContact(const std::string& name, const std::string& phone) {
        contacts.push_back({name, phone});
        std::cout << "Kişi eklendi: " << name << " (" << phone << ")\n";
    }

    void searchContact(const std::string& query) {
        bool found = false;
        for (const auto& contact : contacts) {
            if (contact.name == query || contact.phone == query) {
                std::cout << "Kişi bulundu: " << contact.name << " - " << contact.phone << "\n";
                found = true;
            }
        }
        if (!found) {
            std::cout << "Kişi bulunamadı.\n";
        }
    }

    void listContacts() {
        if (contacts.empty()) {
            std::cout << "Rehberde kayıtlı kişi yok.\n";
        } else {
            std::cout << "Rehber:\n";
            for (const auto& contact : contacts) {
                std::cout << contact.name << " - " << contact.phone << "\n";
            }
        }
    }

    void deleteContact(const std::string& query) {
        auto it = std::remove_if(contacts.begin(), contacts.end(), [&query](const Person& contact) {
            return contact.name == query || contact.phone == query;
        });

        if (it != contacts.end()) {
            contacts.erase(it, contacts.end());
            std::cout << "Kişi silindi.\n";
        } else {
            std::cout << "Kişi bulunamadı.\n";
        }
    }
};

void showMenu() {
    std::cout << "\n1. Kişi Ekle\n"
              << "2. Kişi Ara\n"
              << "3. Tüm Kişileri Listele\n"
              << "4. Kişi Sil\n"
              << "5. Çıkış\n"
              << "Seçiminizi yapın: ";
}

int main() {
    PhoneBook phoneBook;
    int choice;
    do {
        showMenu();
        std::cin >> choice;
        std::cin.ignore(); // Yeni satır karakterini temizle
        switch (choice) {
            case 1: {
                std::string name, phone;
                std::cout << "İsim: ";
                std::getline(std::cin, name);
                std::cout << "Telefon: ";
                std::getline(std::cin, phone);
                phoneBook.addContact(name, phone);
                break;
            }
            case 2: {
                std::string query;
                std::cout << "Arama (isim/telefon): ";
                std::getline(std::cin, query);
                phoneBook.searchContact(query);
                break;
            }
            case 3:
                phoneBook.listContacts();
                break;
            case 4: {
                std::string query;
                std::cout << "Silinecek kişi (isim/telefon): ";
                std::getline(std::cin, query);
                phoneBook.deleteContact(query);
                break;
            }
            case 5:
                std::cout << "Çıkış yapılıyor...\n";
                break;
            default:
                std::cout << "Geçersiz seçim. Tekrar deneyin.\n";
        }
    } while (choice != 5);

    return 0;
}
