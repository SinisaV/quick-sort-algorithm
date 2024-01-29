#include <iostream>
#include <ctime>
#include <cstdlib>

void ZAMENJAJ (int *polje, int pozicija1, int pozicija2) {
    int temp;
    temp = polje[pozicija1];
    polje[pozicija1] = polje[pozicija2];
    polje[pozicija2] = temp;
}

int DELI (int *polje, int dno, int vrh) {
    int mediana;
    mediana = (dno + vrh) / 2;
    ZAMENJAJ(polje, dno, mediana);
    int lIndeks = dno, dIndeks = vrh;
    while (lIndeks < dIndeks) {
        while (polje[lIndeks] <= polje[dno] && lIndeks < vrh) {
            lIndeks++;
        }
        while (polje[dIndeks] >= polje[dno] && dIndeks > dno) {
            dIndeks--;
        }
        if (lIndeks < dIndeks) {
            ZAMENJAJ(polje, dIndeks, lIndeks);
        }
    }
    ZAMENJAJ(polje, dno, dIndeks);
    return dIndeks;
}

int HITRO_UREDI (int *polje, int dno, int vrh) {
    int sredina;
    if (dno < vrh) {
        sredina = DELI(polje, dno, vrh);
        HITRO_UREDI(polje, dno, sredina-1);
        HITRO_UREDI(polje, sredina+1, vrh);
    }
    return 0;
}

bool PREVERI (int *polje, int dno, int vrh) {
    for (int i = dno; i <= vrh - 1; i++) {
        if (polje[i+1] < polje[i]) {
            return false;
        }
    }
    return true;
}

void IZPIS (int *polje, int velikost) {
    for (int i = 0; i <= velikost; i++)
    {
        std::cout << polje[i] << " ";
    }
}

void GENERIRAJ_NAKLJUCNO_ZAPOREDJE (int *polje, int velikost) {
    srand(time(nullptr));
    for (int i = 0; i <= velikost; i++) {
        polje[i] = rand() % 100;
    }
}

void GENERIRAJ_UREJENO_NARASCAJOCE_ZAPOREDJE (int *polje, int velikost) {
    for (int i = 0; i <= velikost; i++) {
        polje[i] = i;
    }
}

void GENERIRAJ_UREJENO_PADAJOCE_ZAPOREDJE (int *polje, int velikost) {
    int j = 0;
    for (int i = velikost; i >= 0; i--) {
        polje[j] = i;
        j++;
    }
}

void MENU () {
    std::cout << "Hitro uredi - izbira:" << std::endl << std::endl;
    std::cout << "1 Generiraj nakljucno zaporedje" << std::endl;
    std::cout << "2 Generiraj urejeno narascajoce zaporedje" << std::endl;
    std::cout << "3 Generiraj urejeno padajoce zaporedje" << std::endl;
    std::cout << "4 Izpis zaporedja" << std::endl;
    std::cout << "5 Uredi" << std::endl;
    std::cout << "6 Konec" << std::endl << std::endl;
    std::cout << "Vasa izbira:";
}
int main() {

    std::cout << "-------QUICKSORT-------" << std::endl;
    int velikost;
    std::cout << "Vnesi dolzino zaporedja: ";
    std::cin >> velikost;
    int *polje = new int[velikost];

    clock_t start, finish;
    double duration;

    bool running = true;
    int selection;

    do {
        MENU();
        std::cin >> selection;
        switch(selection) {
            case 1:
                GENERIRAJ_NAKLJUCNO_ZAPOREDJE(polje, velikost-1);
                break;
            case 2:
                GENERIRAJ_UREJENO_NARASCAJOCE_ZAPOREDJE(polje, velikost-1);
                break;
            case 3:
                GENERIRAJ_UREJENO_PADAJOCE_ZAPOREDJE(polje, velikost-1);
                break;
            case 4:
                IZPIS(polje, velikost-1);
                break;
            case 5:
                if (PREVERI(polje, 0, velikost - 1)) {
                    std::cout << "Zaporedje je ze urejeno" << std::endl;
                    break;
                }
                else if(!PREVERI(polje, 0, velikost - 1)) {
                    //std::cout << "Zaporedje se ni urejeno" << std::endl;
                    start = clock();
                    HITRO_UREDI(polje, 0, velikost-1);
                    finish = clock();
                    duration = (double) (finish - start) / CLOCKS_PER_SEC;
                    std::cout << "Duration: " << duration << std::endl;
                    break;
                }
            case 6:
                running = false;
                break;
            default:
                std::cout << "Napacna izbira!" << std::endl;
                break;
        }
        std::cout << std::endl;
    } while(running);

    delete [] polje;

    return 0;
}
