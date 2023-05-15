#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

struct Soru {
    string soruMetni;
    vector<string> cevaplar;
    char dogruCevap = 'A';
    int puan = 5;
};

class SoruBankasi {
private:
    vector<Soru> soruBankasi;
    vector<Soru> sinavKagidi;

public:
    void soruEkle();
    void soruCikart();
    void soruYazdir(int indeks);
    void tumSorulariYazdir();
    void soruDegistir();
    void kagitOlustur();
    void kagitSil();
    void sinavOlustur();
};

void SoruBankasi::soruEkle() {
    Soru soru;

    cin.ignore(); // Önceki satýrda girilen newline karakterini temizle

    cout << "Soru metnini girin: ";
    getline(cin, soru.soruMetni);

    cout << "Cevap sayisini girin (2-5 arasinda olmali): ";
    int cevapSayisi;
    cin >> cevapSayisi;

    cin.ignore(); // Önceki satýrda girilen newline karakterini temizle

    for (int i = 0; i < cevapSayisi; i++) {
        cout << "Cevap " << char('A' + i) << ": ";
        string cevap;
        getline(cin, cevap);
        soru.cevaplar.push_back(cevap);
    }

    cout << "Dogru cevabi secin (A-E): ";
    cin >> soru.dogruCevap;

    cout << "Sorunun puanini girin: ";
    cin >> soru.puan;

    soruBankasi.push_back(soru);

    cout << "Soru basariyla eklendi!" << endl;
}

void SoruBankasi::soruCikart() {
    int soruIndeksi;

    cout << "Cikartmak istediginiz sorunun indeksini girin: ";
    cin >> soruIndeksi;

    if (soruIndeksi >= 0 && soruIndeksi < soruBankasi.size()) {
        soruBankasi.erase(soruBankasi.begin() + soruIndeksi);
        cout << "Soru basariyla cikartildi!" << endl;
    }
    else {
        cout << "Gecersiz soru indeksi!" << endl;
    }
}

void SoruBankasi::soruYazdir(int soruIndeksi) {
    if (soruIndeksi >= 0 && soruIndeksi < soruBankasi.size()) {
        const Soru& soru = soruBankasi[soruIndeksi];

        cout << "Soru #" << soruIndeksi << endl;
        cout << "Puan: " << soru.puan << endl;
        cout << "Soru: " << soru.soruMetni << endl;

        for (int i = 0; i < soru.cevaplar.size(); i++) {
            cout << char('A' + i) << ") " << soru.cevaplar[i] << endl;
        }

        cout << "Dogru Cevap: " << soru.dogruCevap << endl;
    }
    else {
        cout << "Gecersiz soru indeksi!" << endl;
    }
}


void SoruBankasi::tumSorulariYazdir() {
    for (int i = 0; i < soruBankasi.size(); i++) {
        //cout << "Soru #" << i << endl;
        soruYazdir(i);
        cout << endl;
    }
}

void SoruBankasi::soruDegistir() {
    int soruIndeksi;

    cout << "Degistirmek istediginiz sorunun indeksini girin: ";
    cin >> soruIndeksi;

    if (soruIndeksi >= 0 && soruIndeksi < soruBankasi.size()) {
        Soru& soru = soruBankasi[soruIndeksi];

        cin.ignore(); // Önceki satýrda girilen newline karakterini temizle

        cout << "Yeni soru metnini girin: ";
        getline(cin, soru.soruMetni);

        cout << "Cevap sayisini girin (2-5 arasinda olmali): ";
        int cevapSayisi;
        cin >> cevapSayisi;

        cin.ignore(); // Önceki satýrda girilen newline karakterini temizle

        soru.cevaplar.clear();

        for (int i = 0; i < cevapSayisi; i++) {
            cout << "Cevap " << char('A' + i) << ": ";
            string cevap;
            getline(cin, cevap);
            soru.cevaplar.push_back(cevap);
        }

        cout << "Dogru cevabi secin (A-E): ";
        cin >> soru.dogruCevap;

        cout << "Sorunun puanini girin: ";
        cin >> soru.puan;

        cout << "Soru basariyla degistirildi!" << endl;
    }
    else {
        cout << "Gecersiz soru indeksi!" << endl;
    }
}

void SoruBankasi::kagitOlustur() {
    vector<int> secilenSorular;
    int toplamPuan = 0;

    cout << "Kagit icin soru secimi:" << endl;
    while (true) {
        cout << "Secmek istediginiz sorunun indeksini (-1 toplamayi bitirir) girin: ";
        int soruIndeksi;
        cin >> soruIndeksi;

        if (soruIndeksi == -1) {
            break;
        }

        if (soruIndeksi >= 0 && soruIndeksi < soruBankasi.size()) {
            secilenSorular.push_back(soruIndeksi);
            toplamPuan += soruBankasi[soruIndeksi].puan;
        }
        else {
            cout << "Gecersiz soru indeksi!" << endl;
        }
    }

    sinavKagidi.clear();
    for (int soruIndeksi : secilenSorular) {
        sinavKagidi.push_back(soruBankasi[soruIndeksi]);
    }

    cout << "Kagit basariyla olusturuldu!" << endl;
    cout << "Kagit Toplam Puaný: " << toplamPuan << endl;
}

void SoruBankasi::kagitSil() {
    sinavKagidi.clear();
    cout << "Kagit basariyla silindi!" << endl;
}

void SoruBankasi::sinavOlustur() {
    int maksimumPuan = 0;

    for (const Soru& soru : sinavKagidi) {
        maksimumPuan += soru.puan;
    }

    if (maksimumPuan == 50) {
        maksimumPuan = 100;
    }

    int alinanPuan = 0;

    cout << "Sinava baslayin!" << endl;

    for (int i = 0; i < sinavKagidi.size(); i++) {
        const Soru& soru = sinavKagidi[i];

        cout << "Soru #" << i + 1 << endl;
        cout << "Puan: " << soru.puan << endl;
        cout << "Soru: " << soru.soruMetni << endl;

        for (int j = 0; j < soru.cevaplar.size(); j++) {
            cout << char('A' + j) << ") " << soru.cevaplar[j] << endl;
        }

        cout << "Cevabinizi girin (A-E): ";
        char cevap;
        cin >> cevap;

        if (cevap == soru.dogruCevap) {
            alinanPuan += soru.puan;
        }
        else {
            cout << "Dogru Cevap: " << soru.dogruCevap << endl;
        }

        cout << endl;
    }

    if (maksimumPuan == 100) {
        double puanOrani = static_cast<double>(alinanPuan) / maksimumPuan * 100;
        cout << "Sinav tamamlandi!" << endl;
        cout << "Alinan Puan: " << alinanPuan << endl;
        cout << "Maksimum Puan: " << maksimumPuan << endl;
        cout << "Puan Orani: " << puanOrani << "%" << endl;
    }
    else {
        int endekslenmisPuan = static_cast<int>(static_cast<double>(alinanPuan) / maksimumPuan * 100);
        cout << "Sinav tamamlandi!" << endl;
        cout << "Alinan Puan: " << alinanPuan << endl;
        cout << "Maksimum Puan: " << maksimumPuan << endl;
        cout << "Endekslenmis Puan: " << endekslenmisPuan << endl;
    }
}


int main() {
    SoruBankasi sb;

    int secim;

    do {
        cout << "----- Soru Bankasi Programi -----" << endl;
        cout << "1. Soru Ekle" << endl;
        cout << "2. Soru Cikart" << endl;
        cout << "3. Soru Yazdir" << endl;
        cout << "4. Tum Sorulari Yazdir" << endl;
        cout << "5. Soru Degistir" << endl;
        cout << "6. Kagit Olustur" << endl;
        cout << "7. Kagit Sil" << endl;
        cout << "8. Sinav Olustur" << endl;
        cout << "9. Cikis" << endl;
        cout << "Seciminizi yapin: ";
        cin >> secim;

        switch (secim) {
        case 1:
            sb.soruEkle();
            break;
        case 2:
            sb.soruCikart();
            break;
        case 3: {
            int indeks;
            cout << "Goruntulemek istediginiz sorunun indeksini girin: ";
            cin >> indeks;
            sb.soruYazdir(indeks);
            break;
        }
        case 4:
            sb.tumSorulariYazdir();
            break;
        case 5:
            sb.soruDegistir();
            break;
        case 6:
            sb.kagitOlustur();
            break;
        case 7:
            sb.kagitSil();
            break;
        case 8:
            sb.sinavOlustur();
            break;
        case 9:
            cout << "Programdan cikis yapiliyor..." << endl;
            break;
        default:
            cout << "Gecersiz secim! Tekrar deneyin." << endl;
        }

        cout << endl;

    } while (secim != 9);

    return 0;
}