#include <stdio.h>
#include <string.h>

#define MAX 100

struct Product
{
    int productID;
    char productName[50];
    char category[30];
    float price;
    float rating;
    int stock;
};

/* Function declarations */
void addProducts(struct Product p[], int n);
void displayProducts(struct Product p[], int n);
void linearSearch(struct Product p[], int n);
void bubbleSort(struct Product p[], int n);
void binarySearch(struct Product p[], int n);
void cheapestProduct(struct Product p[], int n);
void mostExpensiveProduct(struct Product p[], int n);
void highestRatedProduct(struct Product p[], int n);
void topFive(struct Product p[], int n);
void priceRange(struct Product p[], int n);

int main()
{
    struct Product products[MAX];
    int n, choice;

    printf("Enter number of products: ");
    scanf("%d", &n);

    if (n > MAX)
    {
        printf("Maximum %d products allowed.\n", MAX);
        return 0;
    }

    addProducts(products, n);

    do
    {
        printf("\n========================================\n");
        printf("   E-COMMERCE PRODUCT MANAGEMENT SYSTEM\n");
        printf("========================================\n");

        printf("1. Display Products\n");
        printf("2. Linear Search by Product ID\n");
        printf("3. Sort Products by Price\n");
        printf("4. Binary Search by Product ID\n");
        printf("5. Cheapest Product\n");
        printf("6. Most Expensive Product\n");
        printf("7. Highest Rated Product\n");
        printf("8. Top 5 Highest-Priced Products\n");
        printf("9. Price Range Search\n");
        printf("0. Exit\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                displayProducts(products, n);
                break;

            case 2:
                linearSearch(products, n);
                break;

            case 3:
                bubbleSort(products, n);
                printf("\nProducts sorted by price successfully!\n");
                displayProducts(products, n);
                break;

            case 4:
                binarySearch(products, n);
                break;

            case 5:
                cheapestProduct(products, n);
                break;

            case 6:
                mostExpensiveProduct(products, n);
                break;

            case 7:
                highestRatedProduct(products, n);
                break;

            case 8:
                topFive(products, n);
                break;

            case 9:
                priceRange(products, n);
                break;

            case 0:
                printf("\nExiting program...\n");
                break;

            default:
                printf("\nInvalid choice!\n");
        }

    } while (choice != 0);

    return 0;
}
//add products
void addProducts(struct Product p[], int n)
{
    int i;

    printf("\nEnter Product Details\n");

    for (i = 0; i < n; i++)
    {
        printf("\nProduct %d\n", i + 1);

        printf("Product ID: ");
        scanf("%d", &p[i].productID);

        printf("Product Name: ");
        scanf(" %[^\n]", p[i].productName);

        printf("Category: ");
        scanf(" %[^\n]", p[i].category);

        printf("Price: ");
        scanf("%f", &p[i].price);

        printf("Rating: ");
        scanf("%f", &p[i].rating);

        printf("Stock Quantity: ");
        scanf("%d", &p[i].stock);
    }
}
//display products
void displayProducts(struct Product p[], int n)
{
    int i;

    printf("\n---------------------------------------------------------------------\n");
    printf("ID\tName\t\tCategory\tPrice\tRating\tStock\n");
    printf("---------------------------------------------------------------------\n");

    for (i = 0; i < n; i++)
    {
        printf("%d\t%-15s %-12s %.2f\t%.1f\t%d\n",
               p[i].productID,
               p[i].productName,
               p[i].category,
               p[i].price,
               p[i].rating,
               p[i].stock);
    }

    printf("---------------------------------------------------------------------\n");
}
/* ==========================================
   LINEAR SEARCH
   ========================================== */

void linearSearch(struct Product p[], int n)
{
    int id, i, found = 0;

    printf("\nEnter Product ID to search: ");
    scanf("%d", &id);

    for (i = 0; i < n; i++)
    {
        if (p[i].productID == id)
        {
            printf("\nProduct Found!\n");

            printf("Product ID   : %d\n", p[i].productID);
            printf("Product Name : %s\n", p[i].productName);
            printf("Category     : %s\n", p[i].category);
            printf("Price        : %.2f\n", p[i].price);
            printf("Rating       : %.1f\n", p[i].rating);
            printf("Stock        : %d\n", p[i].stock);

            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("\nProduct not found!\n");
    }
}
//bubble sort by price
void bubbleSort(struct Product p[], int n)
{
    int i, j;
    struct Product temp;
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (p[j].price > p[j + 1].price)
            {
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}
//binary seard id
void binarySearch(struct Product p[], int n)
{
    int id;
    int low = 0;
    int high = n - 1;
    int mid;
    int found = 0;

    printf("\nNOTE: Binary Search requires the array to be sorted by Product ID.\n");

    printf("Enter Product ID to search: ");
    scanf("%d", &id);

    while (low <= high)
    {
        mid = (low + high) / 2;

        if (p[mid].productID == id)
        {
            printf("\nProduct Found!\n");

            printf("Product ID   : %d\n", p[mid].productID);
            printf("Product Name : %s\n", p[mid].productName);
            printf("Category     : %s\n", p[mid].category);
            printf("Price        : %.2f\n", p[mid].price);
            printf("Rating       : %.1f\n", p[mid].rating);
            printf("Stock        : %d\n", p[mid].stock);

            found = 1;
            break;
        }
        else if (p[mid].productID < id)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }

    if (!found)
    {
        printf("\nProduct not found!\n");
    }
}
//cheapest product
void cheapestProduct(struct Product p[], int n)
{
    int i, min = 0;

    for (i = 1; i < n; i++)
    {
        if (p[i].price < p[min].price)
        {
            min = i;
        }
    }

    printf("\n===== CHEAPEST PRODUCT =====\n");
    printf("Product ID   : %d\n", p[min].productID);
    printf("Product Name : %s\n", p[min].productName);
    printf("Price        : %.2f\n", p[min].price);
}
//most expensive product
void mostExpensiveProduct(struct Product p[], int n)
{
    int i, max = 0;

    for (i = 1; i < n; i++)
    {
        if (p[i].price > p[max].price)
        {
            max = i;
        }
    }

    printf("\n===== MOST EXPENSIVE PRODUCT =====\n");
    printf("Product ID   : %d\n", p[max].productID);
    printf("Product Name : %s\n", p[max].productName);
    printf("Price        : %.2f\n", p[max].price);
}
//highest rated product
void highestRatedProduct(struct Product p[], int n)
{
    int i, max = 0;

    for (i = 1; i < n; i++)
    {
        if (p[i].rating > p[max].rating)
        {
            max = i;
        }
    }

    printf("\n===== HIGHEST RATED PRODUCT =====\n");
    printf("Product ID   : %d\n", p[max].productID);
    printf("Product Name : %s\n", p[max].productName);
    printf("Rating       : %.1f\n", p[max].rating);
}
//top 5 highest priced products
void topFive(struct Product p[], int n)
{
    struct Product temp[MAX];
    int i, j, limit;
    struct Product swap;

    /* Copy original array */
    for (i = 0; i < n; i++)
    {
        temp[i] = p[i];
    }

    /* Bubble sort in descending order */
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (temp[j].price < temp[j + 1].price)
            {
                swap = temp[j];
                temp[j] = temp[j + 1];
                temp[j + 1] = swap;
            }
        }
    }

    limit = (n < 5) ? n : 5;

    printf("\n===== TOP %d HIGHEST-PRICED PRODUCTS =====\n", limit);

    for (i = 0; i < limit; i++)
    {
        printf("%d. %s - %.2f\n",
               i + 1,
               temp[i].productName,
               temp[i].price);
    }
}

void priceRange(struct Product p[], int n)
{
    float minPrice, maxPrice;
    int i, found = 0;

    printf("\nEnter minimum price: ");
    scanf("%f", &minPrice);

    printf("Enter maximum price: ");
    scanf("%f", &maxPrice);

    printf("\nProducts between %.2f and %.2f:\n",
           minPrice, maxPrice);

    for (i = 0; i < n; i++)
    {
        if (p[i].price >= minPrice &&
            p[i].price <= maxPrice)
        {
            printf("%d\t%s\t%.2f\n",
                   p[i].productID,
                   p[i].productName,
                   p[i].price);

            found = 1;
        }
    }

    if (!found)
    {
        printf("No products found in this price range.\n");
    }
}