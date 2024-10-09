#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struktur untuk representasi mata kuliah
struct Matkul {
    char kode[10];
    char nama[50];
    int sks;
    struct Matkul* left;
    struct Matkul* right;
    int height; // Tinggi simpul untuk AVL Tree
};

// Fungsi untuk mencari simpul dengan kode tertentu dalam BST
struct Matkul* cariSimpulBST(struct Matkul* root, const char* kode) {
    if (root == NULL || strcmp(kode, root->kode) == 0) {
        return root;
    }

    if (strcmp(kode, root->kode) < 0) {
        return cariSimpulBST(root->left, kode);
    }

    return cariSimpulBST(root->right, kode);
}

// Fungsi untuk mendapatkan tinggi simpul pada AVL Tree
int tinggi(struct Matkul* node) {
    if (node == NULL) {
        return 0;
    }
    return node->height;
}

// Fungsi untuk mendapatkan maksimum dari dua bilangan
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Fungsi untuk membuat simpul baru pada BST
struct Matkul* buatSimpulBST(const char* kode, const char* nama, int sks) {
    struct Matkul* node = (struct Matkul*)malloc(sizeof(struct Matkul));
    strcpy(node->kode, kode);
    strcpy(node->nama, nama);
    node->sks = sks;
    node->left = node->right = NULL;
    return node;
}

struct Matkul* buatSimpulAVL(const char* kode, const char* nama, int sks) {
    struct Matkul* node = (struct Matkul*)malloc(sizeof(struct Matkul));
    strcpy(node->kode, kode);
    strcpy(node->nama, nama);
    node->sks = sks;
    node->left = node->right = NULL;
    node->height = 1;  // Initialize height for AVL
    return node;
}

// Fungsi untuk menambahkan simpul ke dalam BST
struct Matkul* tambahkeBST(struct Matkul* root, const char* kode, const char* nama, int sks) {
    if (root == NULL) {
        return buatSimpulBST(kode, nama, sks);
    }

    if (strcmp(kode, root->kode) < 0) {
        root->left = tambahkeBST(root->left, kode, nama, sks);
    } else if (strcmp(kode, root->kode) > 0) {
        root->right = tambahkeBST(root->right, kode, nama, sks);
    }

    return root;
}

// Fungsi untuk melakukan rotasi ke kanan pada AVL Tree
struct Matkul* rotateRight(struct Matkul* y) {
    struct Matkul* x = y->left;
    struct Matkul* T2 = x->right;

    // Melakukan rotasi
    x->right = y;
    y->left = T2;

    // Memperbarui tinggi
    y->height = max(tinggi(y->left), tinggi(y->right)) + 1;
    x->height = max(tinggi(x->left), tinggi(x->right)) + 1;

    return x;
}

// Fungsi untuk melakukan rotasi ke kiri pada AVL Tree
struct Matkul* rotateLeft(struct Matkul* x) {
    struct Matkul* y = x->right;
    struct Matkul* T2 = y->left;

    // Melakukan rotasi
    y->left = x;
    x->right = T2;

    // Memperbarui tinggi
    x->height = max(tinggi(x->left), tinggi(x->right)) + 1;
    y->height = max(tinggi(y->left), tinggi(y->right)) + 1;

    return y;
}

// Fungsi untuk mendapatkan keseimbangan AVL (tinggi anak kiri - tinggi anak kanan)
int getBalance(struct Matkul* node) {
    if (node == NULL) {
        return 0;
    }
    return tinggi(node->left) - tinggi(node->right);
}

// Fungsi untuk memulai proses penambahan simpul ke dalam AVL Tree
struct Matkul* tambahkeAVL(struct Matkul* root, const char* kode, const char* nama, int sks) {
    if (root == NULL) {
        return buatSimpulAVL(kode, nama, sks);
    }

    if (strcmp(kode, root->kode) < 0) {
        root->left = tambahkeAVL(root->left, kode, nama, sks);
    } else if (strcmp(kode, root->kode) > 0) {
        root->right = tambahkeAVL(root->right, kode, nama, sks);
    } else {
        return root; // Duplikat kode tidak diperbolehkan
    }

    // Memperbarui tinggi dari simpul yang baru ditambahkan
    root->height = 1 + max(tinggi(root->left), tinggi(root->right));

    // Mendapatkan keseimbangan dari simpul
    int balance = getBalance(root);

    // 4 Kasus rotasi
    // Kiri Kiri
    if (balance > 1 && strcmp(kode, root->left->kode) < 0) {
        return rotateRight(root);
    }
    // Kanan Kanan
    if (balance < -1 && strcmp(kode, root->right->kode) > 0) {
        return rotateLeft(root);
    }
    // Kiri Kanan
    if (balance > 1 && strcmp(kode, root->left->kode) > 0) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }
    // Kanan Kiri
    if (balance < -1 && strcmp(kode, root->right->kode) < 0) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

// Fungsi untuk mencari simpul dengan kode tertentu dalam AVL Tree
struct Matkul* cariSimpulAVL(struct Matkul* root, const char* kode) {
    if (root == NULL || strcmp(kode, root->kode) == 0) {
        return root;
    }

    if (strcmp(kode, root->kode) < 0) {
        return cariSimpulAVL(root->left, kode);
    }

    return cariSimpulAVL(root->right, kode);
}

// Fungsi untuk menampilkan seluruh mata kuliah pada BST secara inorder
void tampilkanBST(struct Matkul* root) {
    if (root != NULL) {
        tampilkanBST(root->left);
        printf("Kode: %s, Nama: %s, SKS: %d\n", root->kode, root->nama, root->sks);
        tampilkanBST(root->right);
    }
}

// Fungsi untuk menampilkan seluruh mata kuliah pada AVL Tree secara inorder
void tampilkanAVL(struct Matkul* root) {
    if (root != NULL) {
        tampilkanAVL(root->left);
        printf("Kode: %s, Nama: %s, SKS: %d\n", root->kode, root->nama, root->sks);
        tampilkanAVL(root->right);
    }
}

// Fungsi untuk menghapus simpul dengan kode tertentu dari BST
struct Matkul* hapusSimpulBST(struct Matkul* root, const char* kode) {
    if (root == NULL) {
        return root;
    }

    // Mencari simpul yang akan dihapus
    if (strcmp(kode, root->kode) < 0) {
        root->left = hapusSimpulBST(root->left, kode);
    } else if (strcmp(kode, root->kode) > 0) {
        root->right = hapusSimpulBST(root->right, kode);
    } else {
        // Simpul dengan satu anak atau tanpa anak
        if (root->left == NULL) {
            struct Matkul* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Matkul* temp = root->left;
            free(root);
            return temp;
        }

        // Simpul dengan dua anak, mendapatkan anak penerus (in-order successor)
        struct Matkul* temp = root->right;
        while (temp->left != NULL) {
            temp = temp->left;
        }

        // Menyalin data anak penerus ke simpul saat ini
        strcpy(root->kode, temp->kode);
        strcpy(root->nama, temp->nama);
        root->sks = temp->sks;

        // Menghapus anak penerus
        root->right = hapusSimpulBST(root->right, temp->kode);
    }

    return root;
}

// Fungsi untuk menghapus simpul dengan kode tertentu dari AVL Tree
struct Matkul* hapusSimpulAVL(struct Matkul* root, const char* kode) {
    if (root == NULL) {
        return root;
    }

    // Mencari simpul yang akan dihapus
    if (strcmp(kode, root->kode) < 0) {
        root->left = hapusSimpulAVL(root->left, kode);
    } else if (strcmp(kode, root->kode) > 0) {
        root->right = hapusSimpulAVL(root->right, kode);
    } else {
        // Simpul dengan satu anak atau tanpa anak
        if (root->left == NULL) {
            struct Matkul* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Matkul* temp = root->left;
            free(root);
            return temp;
        }

        // Simpul dengan dua anak, mendapatkan anak penerus (in-order successor)
        struct Matkul* temp = root->right;
        while (temp->left != NULL) {
            temp = temp->left;
        }

        // Menyalin data anak penerus ke simpul saat ini
        strcpy(root->kode, temp->kode);
        strcpy(root->nama, temp->nama);
        root->sks = temp->sks;

        // Menghapus anak penerus
        root->right = hapusSimpulAVL(root->right, temp->kode);
    }

    // Memperbarui tinggi dari simpul saat ini
    root->height = 1 + max(tinggi(root->left), tinggi(root->right));

    // Mendapatkan keseimbangan dari simpul
    int balance = getBalance(root);

    // 4 Kasus rotasi
    // Kiri Kiri
    if (balance > 1 && getBalance(root->left) >= 0) {
        return rotateRight(root);
    }
    // Kanan Kanan
    if (balance < -1 && getBalance(root->right) <= 0) {
        return rotateLeft(root);
    }
    // Kiri Kanan
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }
    // Kanan Kiri
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;

}

// Fungsi untuk menyimpan data BST ke file
void saveBSTHelper(FILE* file, struct Matkul* root) {
    if (root != NULL) {
        fprintf(file, "Kode: %s, Nama: %s, SKS: %d\n", root->kode, root->nama, root->sks);
        saveBSTHelper(file, root->left);
        saveBSTHelper(file, root->right);
    }
}

void saveBST(const char* filename, struct Matkul* root) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file for writing");
        return;
    }

    saveBSTHelper(file, root);

    fclose(file);
}

// Fungsi untuk menyimpan data AVL ke file
void saveAVLHelper(FILE* file, struct Matkul* root) {
    if (root != NULL) {
        fprintf(file, "Kode: %s, Nama: %s, SKS: %d\n", root->kode, root->nama, root->sks);
        saveAVLHelper(file, root->left);
        saveAVLHelper(file, root->right);
    }
}

void saveAVL(const char* filename, struct Matkul* root) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file for writing");
        return;
    }

    saveAVLHelper(file, root);

    fclose(file);
}

// Fungsi untuk membaca data dari file dan memasukkan ke dalam BST
struct Matkul* loadBST(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file for reading");
        return NULL;
    }

    struct Matkul* root = NULL;
    char kode[10], nama[50];
    int sks;

    // Membaca data dari file
    while (fscanf(file, "Kode: %9[^,], Nama: %49[^,], SKS: %d\n", kode, nama, &sks) == 3) {
        root = tambahkeBST(root, kode, nama, sks);
    }

    fclose(file);

    return root;
}

// Fungsi untuk membaca data dari file dan memuatnya ke dalam AVL Tree
struct Matkul* loadAVL(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file for reading");
        return NULL;
    }

    struct Matkul* root = NULL;
    char kode[10], nama[50];
    int sks;

    // Membaca data dari file
    while (fscanf(file, "Kode: %9[^,], Nama: %49[^,], SKS: %d\n", kode, nama, &sks) == 3) {
        root = tambahkeAVL(root, kode, nama, sks); // Menambahkan data ke dalam AVL Tree
    }

    fclose(file);

    return root;
}

int main() {
    struct Matkul* rootBST = NULL;
    struct Matkul* rootAVL = NULL;

    int pilihan;
    char kode[10], nama[50];
    int sks;

    // Filename for storing the database
    const char* filename = "database.txt";
    struct Matkul* resultBST = NULL;  // Declare outside the switch
    struct Matkul* resultAVL = NULL;  // Declare outside the switch

    // Check if the database file exists
    FILE* fileCheck = fopen(filename, "r");
    if (fileCheck != NULL) {
        fclose(fileCheck);

        // Check if the data structures are empty or not
        rootBST = loadBST(filename);
        rootAVL = loadAVL(filename);

        // If both BST and AVL are empty, then the file exists but there is no data
        if (rootBST == NULL && rootAVL == NULL) {
            printf("File database ditemukan tetapi tidak ada data.\n");
        }
    } else {
        // File does not exist, create a new file
        printf("File database tidak ditemukan. Membuat file baru...\n");
        FILE* fileCreate = fopen(filename, "w");
        if (fileCreate == NULL) {
            perror("Error creating file");
            return 1;
        }
        fclose(fileCreate);
    }

    do {
        printf("\nMenu:\n");
        printf("1. Gunakan BST\n");
        printf("2. Gunakan AVL Tree\n");
        printf("3. Keluar\n");
        printf("Pilihan: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                // Gunakan BST
                printf("\n=== Menggunakan BST ===\n");
                // Load database from file if available
                rootBST = loadBST(filename);
                do {
                    printf("\nSubmenu BST:\n");
                    printf("1. Tambahkan Mata Kuliah\n");
                    printf("2. Tampilkan Mata Kuliah\n");
                    printf("3. Cari Mata Kuliah\n");
                    printf("4. Hapus Mata Kuliah\n");
                    printf("5. Kembali ke Menu Utama\n");
                    printf("Pilihan: ");
                    scanf("%d", &pilihan);

                    switch (pilihan) {
                        case 1:
                            // Tambahkan mata kuliah pada BST
                            printf("\nMasukkan Kode Mata Kuliah: ");
                            scanf("%s", kode);
                            getchar(); // Membersihkan buffer
                            printf("Masukkan Nama Mata Kuliah: ");
                            fgets(nama, sizeof(nama), stdin);
                            nama[strcspn(nama, "\n")] = '\0'; // Menghapus newline dari fgets
                            printf("Masukkan SKS Mata Kuliah: ");
                            scanf("%d", &sks);
                            rootBST = tambahkeBST(rootBST, kode, nama, sks);
                            break;
                        case 2:
                            // Tampilkan mata kuliah pada BST
                            printf("\nMata Kuliah (BST):\n");
                            tampilkanBST(rootBST);
                            break;
                        case 3:
                             // Cari mata kuliah pada BST
                            printf("\nMasukkan Kode Mata Kuliah yang Ingin Dicari: ");
                            scanf("%s", kode);
                            resultBST = cariSimpulBST(rootBST, kode);
                            if (resultBST != NULL) {
                                printf("Mata Kuliah ditemukan (BST): Kode: %s, Nama: %s, SKS: %d\n", resultBST->kode, resultBST->nama, resultBST->sks);
                            } else {
                                printf("Mata Kuliah tidak ditemukan (BST).\n");
                            }
                            break;
                        case 4:
                            // Hapus mata kuliah pada BST
                            printf("\nMasukkan Kode Mata Kuliah yang Ingin Dihapus: ");
                            scanf("%s", kode);
                            resultBST = cariSimpulBST(rootBST, kode);
                            if (resultBST != NULL) {
                                rootBST = hapusSimpulBST(rootBST, kode);
                                printf("Mata Kuliah dengan Kode %s telah dihapus dari BST.\n", kode);
                            } else {
                                printf("Mata Kuliah dengan Kode %s tidak ditemukan.\n", kode);
                            }
                            break;
                        case 5:
                            // Kembali ke Menu Utama
                            break;
                        default:
                            printf("\nPilihan tidak valid. Silakan coba lagi.\n");
                    }
                } while (pilihan != 5);
                
                saveBST(filename, rootBST); // Menyimpan perubahan BST kembali ke file
                break;

            case 2:
                // Gunakan AVL Tree
                printf("\n=== Menggunakan AVL Tree ===\n");
                // Load database from file if available
                rootAVL = loadAVL(filename);
                do {
                    printf("\nSubmenu AVL Tree:\n");
                    printf("1. Tambahkan Mata Kuliah\n");
                    printf("2. Tampilkan Mata Kuliah\n");
                    printf("3. Cari Mata Kuliah\n");
                    printf("4. Hapus Mata Kuliah\n");
                    printf("5. Kembali ke Menu Utama\n");
                    printf("Pilihan: ");
                    scanf("%d", &pilihan);

                    switch (pilihan) {
                        case 1:
                            // Tambahkan mata kuliah pada AVL Tree
                            printf("\nMasukkan Kode Mata Kuliah: ");
                            scanf("%s", kode);
                            getchar(); // Membersihkan buffer
                            printf("Masukkan Nama Mata Kuliah: ");
                            fgets(nama, sizeof(nama), stdin);
                            nama[strcspn(nama, "\n")] = '\0'; // Menghapus newline dari fgets
                            printf("Masukkan SKS Mata Kuliah: ");
                            scanf("%d", &sks);
                            rootAVL = tambahkeAVL(rootAVL, kode, nama, sks);
                            break;
                        case 2:
                            // Tampilkan mata kuliah pada AVL Tree
                            printf("\nMata Kuliah (AVL Tree):\n");
                            tampilkanAVL(rootAVL);
                            break;
                        case 3:
                            // Cari mata kuliah pada AVL Tree
                            printf("\nMasukkan Kode Mata Kuliah yang Ingin Dicari: ");
                            scanf("%s", kode);
                            resultAVL = cariSimpulAVL(rootAVL, kode);
                            if (resultAVL != NULL) {
                                printf("Mata Kuliah ditemukan (AVL Tree): Kode: %s, Nama: %s, SKS: %d\n", resultAVL->kode, resultAVL->nama, resultAVL->sks);
                            } else {
                                printf("Mata Kuliah tidak ditemukan.\n");
                            }
                            break;
                        case 4:
                            // Hapus mata kuliah pada AVL Tree
                            printf("\nMasukkan Kode Mata Kuliah yang Ingin Dihapus: ");
                            scanf("%s", kode);
                            resultAVL = cariSimpulAVL(rootAVL, kode);
                            if (resultAVL != NULL) {
                                rootAVL = hapusSimpulAVL(rootAVL, kode);
                                printf("Mata Kuliah dengan Kode %s telah dihapus dari AVL Tree.\n", kode);
                            } else {
                                printf("Mata Kuliah dengan Kode %s tidak ditemukan.\n", kode);
                            }
                            break;
                        case 5:
                            // Kembali ke Menu Utama
                            break;
                        default:
                            printf("\nPilihan tidak valid. Silakan coba lagi.\n");
                    }
                } while (pilihan != 5);
                
                // Save database to file
                saveAVL(filename, rootAVL); // Menyimpan perubahan AVL kembali ke file
                break;

            case 3:
                // Keluar
                printf("\nProgram Berakhir. Sampai Jumpa!\n");
                break;

            default:
                printf("\nPilihan tidak valid. Silakan coba lagi.\n");
        }

    } while (pilihan != 3);

    return 0;
}
