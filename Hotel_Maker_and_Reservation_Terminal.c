#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct reservationNode
{
    int nightsOfStay;
    int totalPrice;
    int numberOfGuests;
    char confirmationNumber[10];
    char *reservationName;
    char *phoneNumber;
    char *mailAddress;
    struct reservationNode *next;
} RESERVATION;

typedef struct hotelNode
{
    int hotelRefNumber;
    int priceForNight;
    int totalRooms;
    int availableRooms;
    char *hotelName;
    struct hotelNode *next;
    RESERVATION *beta;
} HOTEL;
HOTEL *alpha;

struct getReturnValue
{
    HOTEL *ptrToHotelNode;
    RESERVATION *ptrToReservationNode;
};

// The return values of these char* functions are dynamically allocated so do please free them after use.
char *getString(const char *printStatement);
char *getName(const char *printStatement);
char getChar(const char *printStatement);
char getUserConfirmation(char confirm);
int getInt(const char *printStatement);
int *countInput(char *ptrStringInput, char inputType, int outputArray[]);
void adminPassword(const char *actualPassword, int *trys);
void adminControl();
void modifyHotelAttribute();
void reservationDetails(const int *extraCharge);
void changeReservation(const int *extraCharge);
void getHotelNode();
void insertHotelNode(HOTEL *temp1, HOTEL *left);
void getReservationNode(const int *extraCharge);
char *getConfirmationNumber(char *reservationString, int hotelRefNumber);
char *transferStringToNode(char *input_string, char *destination);
void printLinkedList();
void printReservationList();
void printSpecificHotel(HOTEL *ptrToHotelNode);
void printSpecificReservation(HOTEL *ptrToHotelNode, RESERVATION *ptrToReservationNode);
void reverseLinkedList(HOTEL *ptrToNode);
void deleteHotelNode();
void deleteReservationNode();
void deleteSpecificReservationNode(RESERVATION **freeReservationNode);
HOTEL *findHotelNode(HOTEL *ptrToHotelNode);
struct getReturnValue findReservationNode();
int checkIfReservationEmpty(HOTEL **ptrToHotelNode, RESERVATION **ptrToReservationNode);
int getReferenceNumberOfHotel(HOTEL **getCorrespondingHotelNode);
int findHotelNodeViaConfirmationNumber(HOTEL **findCorrespondingHotelNode, char *findConfirmationNumber);
int READ_CSV_DATA();
void STORE_CSV_DATA(HOTEL *storeHotelIntoFile);
void freeLinkedList();
void abortProcess(const char *exitMessage);

int main(void)
{
    alpha = NULL;
    const int extraCharge = 2000;
    const int nodeCount = 3;
    int trys = 4;
    const char *actualPassword = "ungalag";

    int tripSwitch = READ_CSV_DATA();

    if (tripSwitch == 1)
    {
        for (int i = 0; i < nodeCount; i++)
        {
            getHotelNode();
            printLinkedList();
        }
    }
    else
    {
        printf("\n");
    }

    int selection;
    char confirm;
    do
    {
        printf("≪:۩:••:۩:••:۩:••:۩:≫ ──── ««•{⋆⋆⋆}•»» ──── ≪:۩:••:۩:••:۩:••:۩:≫\n");
        printf("WELCOME GUEST! THIS IS THE OPERATING TERMINAL OF IMAGINARY HOTEL\n");
        printf("─★─────────★─────────★─────────★─────────★─────────★─────────★─\n\n");
        printf("Type in the number to make your selection:\n");
        selection = getInt("1.) Make A Reservation With Us!\n2.) Reservation Details\n3.) Admin Control\n4.) <<<EXIT PROGRAM>>>\n\nInput Here---> ");
        printf("\n");

        switch (selection)
        {
            case 1:
            {
                printLinkedList();
                getReservationNode(&extraCharge);
                break;
            }

            case 2:
            {
                reservationDetails(&extraCharge);
                break;
            }

            case 3:
            {
                adminPassword(actualPassword, &trys);
                break;
            }

            case 4:
            {
                confirm = getUserConfirmation(confirm);

                if (confirm == 'Y' || confirm == 'y')
                {
                    printf("SHUTTING DOWN...");
                    STORE_CSV_DATA(alpha);
                    return 0;
                }
                else
                {
                    selection = 0;
                }
                break;
            }

            default:
            {
                printf("<<<NO SUCH ENTRY EXISTS>>>\nPLEASE TRY AGAIN\n\n");
                break;
            }
        }
    }
    while (selection != 4);

    return 0;
}

char *getString(const char *printStatement)
{
    const int INPUT_CHARACTER_LIMIT = 20;
    const int BUFFER_SIZE = 50;
    int alert;
    char *ptrStringInput = (char *) malloc(BUFFER_SIZE * sizeof(char));

    if (ptrStringInput == NULL)
    {
        abortProcess("\n<<<WARNING MEMORY UNABLE TO BE ALLOCATED>>>\n");
    }

    do
    {
        printf("%s", printStatement);
        fgets(ptrStringInput, BUFFER_SIZE, stdin);
        ptrStringInput[strcspn(ptrStringInput, "\n")] = 0;
        alert = 0;
        int ch;

        // output[0] is string length
        // output[1] is non character count
        int outputArray[2];
        countInput(ptrStringInput, 'S', outputArray);

        if (outputArray[0] == outputArray[1] || outputArray[0] - outputArray[1] > INPUT_CHARACTER_LIMIT)
        {
            if (outputArray[0] == outputArray[1])
            {
                printf("\n<<<NO INPUT DETECTED>>>\nPLEASE TRY AGAIN\n\n");
            }

            if (outputArray[0] - outputArray[1] > INPUT_CHARACTER_LIMIT)
            {
                printf("\n<<<CHARACTER COUNT EXCEEDED>>>\nKEEP UNDER %d CHARACTERS OR LESS\nINPUTTED CHARACTER COUNT: %d\nPLEASE TRY AGAIN\n\n", INPUT_CHARACTER_LIMIT, outputArray[0] - outputArray[1]);
            }

            if (outputArray[0] == BUFFER_SIZE - 1)
            {
                while ((ch = getchar()) != '\n' && ch != EOF);
            }

            alert = 1;
        }
    }
    while (alert == 1);

    return ptrStringInput;
}

char *getName(const char *printStatement)
{
    int alert;
    char *ptrStringInput;
    do
    {
        alert = 0;
        ptrStringInput = getString(printStatement);

        // outputArray[0] is non alphabetic count
        int outputArray[1];
        countInput(ptrStringInput, 'N', outputArray);

        if (outputArray[0] > 0)
        {
            printf("\n<<<INVALID INPUT DETECTED>>>\nPLEASE TRY AGAIN\n\n");
            alert = 1;
        }
    }
    while (alert == 1);

    return ptrStringInput;
}

char getChar(const char *printStatement)
{
    int alert;
    char *ptrStringInput;
    do
    {
        alert = 0;
        ptrStringInput = getString(printStatement);

        // output[0] is string length
        // output[1] is non character count
        // output[2] is character count
        int outputArray[3];
        countInput(ptrStringInput, 'C', outputArray);

        if (outputArray[2] > 1 || isspace(ptrStringInput[0]))
        {
            printf("\n<<<INPUT ONLY ONE CHARACTER>>>\nPLEASE TRY AGAIN\n\n");
            alert = 1;
        }
    }
    while (alert == 1);

    char convertToChar = ptrStringInput[0];
    free(ptrStringInput);

    return convertToChar;
}

int getInt(const char *printStatement)
{
    int alert;
    char *ptrStringInput;
    do
    {
        alert = 0;
        ptrStringInput = getString(printStatement);

        // outputArray[0] is non digit count
        int outputArray[1];
        countInput(ptrStringInput, 'I', outputArray);

        if (outputArray[0] > 0)
        {
            printf("\n<<<INVALID INPUT DETECTED>>>\nPLEASE TRY AGAIN\n\n");
            alert = 1;
        }
    }
    while (alert == 1);

    int offset = 0;
    int convertToInteger = 0;

    if (ptrStringInput[0] == '-')
    {
        offset = 1;
    }

    for (int i = offset; ptrStringInput[i] != '\0'; i++)
    {
        convertToInteger = convertToInteger * 10 + ptrStringInput[i] - '0';
    }

    if (offset == 1)
    {
        convertToInteger = -convertToInteger;
    }

    free(ptrStringInput);
    return convertToInteger;
}

int *countInput(char *ptrStringInput, char inputType, int outputArray[])
{
    if (inputType == 'S' || inputType == 'C')
    {
        // output[0] is string length
        // output[1] is non character count
        // output[2] is character count
        outputArray[0] = strlen(ptrStringInput);
        outputArray[1] = 0;
        outputArray[2] = 0;
        for (int i = 0; i < outputArray[0]; i++)
        {
            if (isspace(ptrStringInput[i]))
            {
                outputArray[1]++;
            }
            else
            {
                outputArray[2]++;
            }
        }
    }

    if (inputType == 'N')
    {
        // outputArray[0] is non alphabetic count
        outputArray[0] = 0;
        for (int i = 0; ptrStringInput[i] != '\0'; i++)
        {
            if (!isalpha(ptrStringInput[i]) && !isspace(ptrStringInput[i]))
            {
                outputArray[0]++;
            }
        }
    }

    if (inputType == 'I')
    {
        // outputArray[0] is non digit count
        outputArray[0] = 0;
        for (int i = 0; ptrStringInput[i] != '\0'; i++)
        {
            if (!((ptrStringInput[i] >= '0') && (ptrStringInput[i] <= '9')))
            {
                outputArray[0]++;
            }
        }

        if (ptrStringInput[0] == '-')
        {
            outputArray[0]--;
        }
    }
    return outputArray;
}

char getUserConfirmation(char confirm)
{
    for (;;)
    {
        confirm = getChar("Proceed[Y/N]: ");
        printf("\n");

        if (confirm == 'Y' || confirm == 'N' || confirm == 'y' || confirm == 'n')
        {
            break;
        }
    }

    return confirm;
}

void adminPassword(const char *actualPassword, int *trys)
{

    if ((*trys) == 0)
    {
        printf("<<<UNAUTHORIZED ACCESS DETECTED>>>\n\n");
        return;
    }

    char confirm;
    char *passwordForAdminControl;
    do
    {
        passwordForAdminControl = getString("Password: ");
        printf("\n");

        if (strcmp(passwordForAdminControl, actualPassword) == 0)
        {
            free(passwordForAdminControl);
            adminControl();
            break;
        }
        else
        {
            free(passwordForAdminControl);
            printf("<<<WRONG PASSWORD>>>\nYou have %d tries left\n", ((*trys)) - 1);
            ((*trys))--;

            if (((*trys)) == 0)
            {
                printf("<<<SYSTEM LOCK ACTIVATED>>>\n\n");
                break;
            }

            for (;;)
            {
                confirm = getChar("Try Again[Y/N]: ");
                printf("\n");

                if (confirm == 'Y' || confirm == 'N' || confirm == 'y' || confirm == 'n')
                {
                    break;
                }
            }

            if (confirm == 'N' || confirm == 'n')
            {
                break;
            }
        }
    }
    while (confirm == 'Y' || confirm == 'y');
}

void adminControl()
{
    int selection;
    char confirm;
    do
    {
        selection = getInt("WELCOME ADMIN\n\n1.) Print Hotel List\n2.) Modify Hotel Attributes\n3.) Add A New Hotel Node\n4.) Delete A Hotel Node\n5.) Reverse Viewing List For Shits and Giggles\n6.) Close\n\nInput Here---> ");
        printf("\n");

        switch (selection)
        {
            case 1:
            {
                printLinkedList();
                break;
            }

            case 2:
            {
                printLinkedList();
                modifyHotelAttribute();
                break;
            }

            case 3:
            {
                printf("You have selected to add a new hotel node\n");
                confirm = getUserConfirmation(confirm);

                if (confirm == 'Y' || confirm == 'y')
                {
                    getHotelNode();
                }
                break;
            }

            case 4:
            {
                printf("You have selected to delete a hotel node\n");
                confirm = getUserConfirmation(confirm);

                if (confirm == 'Y' || confirm == 'y')
                {
                    printLinkedList();
                    deleteHotelNode();
                }
                break;
            }

            case 5:
            {
                reverseLinkedList(alpha);
                printLinkedList();
                break;
            }

            case 6:
            {
                break;
            }

            default:
            {
                printf("<<<NO SUCH ENTRY EXISTS>>>\nPLEASE TRY AGAIN\n\n");
                break;
            }
        }
    }
    while (selection != 6);
}

void modifyHotelAttribute()
{
    char confirm;
    HOTEL *ptrToHotelNode = NULL;
    ptrToHotelNode = findHotelNode(ptrToHotelNode);

    printf("You have chosen:\n");
    printSpecificHotel(ptrToHotelNode);

    int newPrice;
    do
    {
        do
        {
            newPrice = getInt("What will the new price be? ");

            if (newPrice > 50000 || newPrice < 9000)
            {
                printf("\n<<<BY REGULATION THE STANDARD PRICE MUST BE BETWEEN 9000 and 50000>>>\nPLEASE TRY AGAIN\n\n");
            }
        }
        while (newPrice > 50000 || newPrice < 9000);

        printf("The standard price for 1 night of IMAGINARY HOTEL <%s> will be changed from ¥%d to ¥%d\n", ptrToHotelNode->hotelName, ptrToHotelNode->priceForNight, newPrice);
        confirm = getUserConfirmation(confirm);
    }
    while (confirm == 'N' || confirm == 'n');

    if (confirm == 'Y' || confirm == 'y')
    {
        ptrToHotelNode->priceForNight = newPrice;
    }

    return;
}

void reservationDetails(const int *extraCharge)
{
    int selection;
    char confirm;
    do
    {
        selection = getInt("RESERVATION DETAILS\n\n1.) Print My Reservations\n2.) Change My Reservation\n3.) Cancel My Reservation\n4.) Close\n\nInput Here---> ");
        printf("\n");
        switch (selection)
        {
            case 1:
            {
                printReservationList();
                break;
            }

            case 2:
            {
                printf("You have selected to change a reservation\n");
                confirm = getUserConfirmation(confirm);

                if (confirm == 'Y' || confirm == 'y')
                {
                    printReservationList();
                    changeReservation(extraCharge);
                }
                break;
            }

            case 3:
            {
                printf("You have selected to cancel a reservation\n");
                confirm = getUserConfirmation(confirm);

                if (confirm == 'Y' || confirm == 'y')
                {
                    printReservationList();
                    deleteReservationNode();
                }
                break;
            }

            case 4:
            {
                break;
            }

            default:
            {
                printf("<<<NO SUCH ENTRY EXISTS>>>\nPLEASE TRY AGAIN\n\n");
                break;
            }
        }
    }
    while (selection != 4);
}

void changeReservation(const int *extraCharge)
{
    char confirm;
    struct getReturnValue HR;
    HR.ptrToHotelNode = NULL;
    HR.ptrToReservationNode = NULL;
    do
    {
        HR = findReservationNode();

        if (HR.ptrToHotelNode == NULL && HR.ptrToReservationNode == NULL)
        {
            return;
        }

        printf("You have chosen:\n");
        printSpecificReservation(HR.ptrToHotelNode, HR.ptrToReservationNode);
        confirm = getUserConfirmation(confirm);
    }
    while (confirm == 'N' || confirm == 'n');

    int newNightsOfStay = 0;
    int calcNewPrice = 0;
    do
    {
        do
        {
            newNightsOfStay = getInt("Change your nights of stay: ");
            printf("\n");

            if (newNightsOfStay > 30)
            {
                printf("\nThis hotel accepts stayovers of up to 30 days or less\nFor an extended stayover please contact us directly\n\n");
            }
        }
        while (newNightsOfStay < 1 || newNightsOfStay > 30);

        if (HR.ptrToReservationNode->numberOfGuests == 1)
        {
            calcNewPrice = newNightsOfStay * HR.ptrToHotelNode->priceForNight;
        }
        else
        {
            calcNewPrice = newNightsOfStay * (HR.ptrToHotelNode->priceForNight + *extraCharge);
        }

        printf("Your stayover period will change from %d nights into %d nights\nYour total price will change from ¥%d into ¥%d\n", HR.ptrToReservationNode->nightsOfStay, newNightsOfStay, HR.ptrToReservationNode->totalPrice, calcNewPrice);
        confirm = getUserConfirmation(confirm);
    }
    while (confirm == 'N' || confirm == 'n');

    if (confirm == 'Y' || confirm == 'y')
    {
        HR.ptrToReservationNode->nightsOfStay = newNightsOfStay;
        HR.ptrToReservationNode->totalPrice = calcNewPrice;
    }

    return;
}

void getHotelNode()
{
    char *wordInput;
    int input_hotelRefNumber;
    int input_priceForNight;
    int input_totalRooms;
    int alert;
    do
    {
        alert = 0;
        wordInput = getName("Let us make an imaginary hotel chain shall we?\nInput the name of it---> ");
        for (int i = 0; wordInput[i] != '\0'; i++)
        {
            wordInput[i] = toupper(wordInput[i]);
        }

        HOTEL *CheckNameSimilarity = alpha;
        while (CheckNameSimilarity != NULL)
        {
            if (strcmp(CheckNameSimilarity->hotelName, wordInput) == 0)
            {
                printf("\n<<<TWO OR MORE HOTELS CANNOT HARBOR THE EXACT SAME NAME>>>\nPLEASE TRY AGAIN\n\n");
                printLinkedList();
                alert = 1;
                break;
            }
            CheckNameSimilarity = CheckNameSimilarity->next;
        }
    }
    while (alert == 1);

    do
    {
        alert = 0;
        input_hotelRefNumber = getInt("What will it's reference number be: ");

        if (input_hotelRefNumber > 999 || input_hotelRefNumber < 100)
        {
            printf("\n<<<A 3 DIGIT NUMBER MUST BE ENTERED>>>\nPLEASE TRY AGAIN\n\n");
            alert = 1;
        }

        HOTEL *CheckRefNumber = alpha;
        while (CheckRefNumber != NULL)
        {
            if (CheckRefNumber->hotelRefNumber == input_hotelRefNumber)
            {
                printf("\n<<<TWO OR MORE HOTELS CANNOT HARBOR THE SAME REFERENCE NUMBER>>>\nPLEASE TRY AGAIN\n\n");
                printLinkedList();
                alert = 1;
                break;
            }
            CheckRefNumber = CheckRefNumber->next;
        }
    }
    while (alert == 1);

    do
    {
        input_priceForNight = getInt("What will the price be for a single night: ");

        if (input_priceForNight > 50000 || input_priceForNight < 9000)
        {
            printf("\n<<<BY REGULATION THE STANDARD PRICE MUST BE BETWEEN 9000 and 50000>>>\nPLEASE TRY AGAIN\n\n");
        }
    }
    while (input_priceForNight > 50000 || input_priceForNight < 9000);

    do
    {
        input_totalRooms = getInt("What will be total amount of rooms: ");

        if (input_totalRooms > 166)
        {
            printf("\n<<<BY REGULATION THE HOTEL MUST NOT EXCEED 166 ROOMS>>>\nPLEASE TRY AGAIN\n\n");
        }

        if (input_totalRooms == 1)
        {
            printf("\nAn AirBnb?!?\n");
        }
    }
    while (input_totalRooms < 1 || input_totalRooms > 166);

    HOTEL *newHotelNode = (HOTEL *) calloc(1, sizeof(HOTEL));

    if (newHotelNode == NULL)
    {
        abortProcess("\nWARNING MEMORY UNABLE TO BE ALLOCATED\n");
    }

    newHotelNode->hotelName = transferStringToNode(wordInput, newHotelNode->hotelName);
    newHotelNode->hotelRefNumber = input_hotelRefNumber;
    newHotelNode->priceForNight = input_priceForNight;
    newHotelNode->totalRooms = input_totalRooms;
    newHotelNode->availableRooms = input_totalRooms;

    insertHotelNode(newHotelNode, alpha);
    printf("\n");
}

void getReservationNode(const int *extraCharge)
{
    int alert;
    int numberOfGuests = 1;
    char confirm;
    HOTEL *ptrToHotelNode = NULL;
    do
    {
        ptrToHotelNode = findHotelNode(ptrToHotelNode);

        if (ptrToHotelNode->availableRooms == 0)
        {
            printf("<<<FULLY BOOKED>>>\nCome again next time!\n\n");
            return;
        }

        printf("You have chosen:\n");
        printSpecificHotel(ptrToHotelNode);
        confirm = getUserConfirmation(confirm);
    }
    while (confirm == 'N' || confirm == 'n');

    do
    {
        do
        {
            alert = 0;
            numberOfGuests = getInt("How many people will stay: ");
            switch (numberOfGuests)
            {
                case 1:
                {
                    break;
                }

                case 2:
                {
                    printf("A reservation for 2 will add an extra ¥%d per night\n", *extraCharge);
                    break;
                }

                default:
                {
                    printf("\nThis hotel only accepts adult guests of 2 people or less per room\n\n");
                    alert = 1;
                    break;
                }
            }
        }
        while (alert == 1);

        confirm = getUserConfirmation(confirm);
    }
    while (confirm == 'N' || confirm == 'n');

    int nightsOfStay;
    int totalPrice;
    do
    {
        do
        {
            nightsOfStay = getInt("How many nights will you stay: ");

            if (nightsOfStay > 30)
            {
                printf("\nThis hotel accepts stayovers of up to 30 days or less\nFor an extended stayover please contact us directly\n\n");
            }
        }
        while (nightsOfStay < 1 || nightsOfStay > 30);

        if (numberOfGuests == 1)
        {
            totalPrice = nightsOfStay * ptrToHotelNode->priceForNight;
        }
        else
        {
            totalPrice = nightsOfStay * (ptrToHotelNode->priceForNight + *extraCharge);
        }

        printf("\nYou have selected %d nights for ¥%d at IMAGINARY HOTEL <%s>\n", nightsOfStay, totalPrice, ptrToHotelNode->hotelName);
        confirm = getUserConfirmation(confirm);
    }
    while (confirm == 'N' || confirm == 'n');

    printf("Thank you for choosing IMAGINARY HOTEL <%s>\nPlease fill in the following to finalize your reservation\n\n", ptrToHotelNode->hotelName);

    char *input_reservationName;
    input_reservationName = getName("Enter your reservation name(Letters Only): ");

    char *input_phoneNumber;
    input_phoneNumber = getString("Enter your phone number: ");

    char *input_mailAddress;
    int atCount;
    do
    {
        input_mailAddress = getString("Enter your Email address: ");
        atCount = 0;

        for (int i = 0; input_mailAddress[i] != '\0'; i++)
        {
            if (input_mailAddress[i] == '@')
            {
                atCount++;
            }
        }

        if (atCount != 1)
        {
            printf("\n<<<PLEASE WRITE DOWN YOUR EMAIL ADDRESS COMPLETELY>>>\nPLEASE TRY AGAIN\n\n");
        }
    }
    while (atCount != 1);

    RESERVATION *ptrToReservationNode = (RESERVATION *) calloc(1, sizeof(RESERVATION));

    if (ptrToReservationNode == NULL)
    {
        abortProcess("\nWARNING MEMORY UNABLE TO BE ALLOCATED\n");
    }

    char confirmationNumber[10];
    getConfirmationNumber(confirmationNumber, ptrToHotelNode->hotelRefNumber);
    strcpy(ptrToReservationNode->confirmationNumber, confirmationNumber);
    ptrToReservationNode->reservationName = transferStringToNode(input_reservationName, ptrToReservationNode->reservationName);
    ptrToReservationNode->phoneNumber = transferStringToNode(input_phoneNumber, ptrToReservationNode->phoneNumber);
    ptrToReservationNode->mailAddress = transferStringToNode(input_mailAddress, ptrToReservationNode->mailAddress);
    ptrToReservationNode->nightsOfStay = nightsOfStay;
    ptrToReservationNode->totalPrice = totalPrice;
    ptrToReservationNode->numberOfGuests = numberOfGuests;
    ptrToHotelNode->availableRooms--;

    if (ptrToHotelNode->beta == NULL)
    {
        ptrToHotelNode->beta = ptrToReservationNode;
    }
    else
    {
        ptrToReservationNode->next = ptrToHotelNode->beta;
        ptrToHotelNode->beta = ptrToReservationNode;
    }

    printf("\n<<<RESERVATION BOOKED>>>\n");
    printSpecificReservation(ptrToHotelNode, ptrToReservationNode);

    return;
}

char *getConfirmationNumber(char *reservationString, int hotelRefNumber)
{
    int tailReservationNumber = 0;

    FILE *storeReservationNumber = fopen("confirmation_list.csv", "r");
    int read = 0;
    do
    {
        read = fscanf(storeReservationNumber, "%d\n", &tailReservationNumber);

        if (read != 1)
        {
            abortProcess("\nThere is nothing we can do...\n<<<Critical Error in reading a CSV file>>>\n\n");
        }
    }
    while (!feof(storeReservationNumber));

    tailReservationNumber++;
    fclose(storeReservationNumber);

    storeReservationNumber = fopen("confirmation_list.csv", "w");
    fprintf(storeReservationNumber, "%d\n", tailReservationNumber);
    fclose(storeReservationNumber);

    int temp = tailReservationNumber;
    int digitCount = 0;
    do
    {
        temp /= 10;
        digitCount++;
    }
    while (temp != 0);

    switch (digitCount)
    {
        case 1:
            sprintf(reservationString, "00000%d%d", tailReservationNumber, hotelRefNumber);
            break;

        case 2:
            sprintf(reservationString, "0000%d%d", tailReservationNumber, hotelRefNumber);
            break;

        case 3:
            sprintf(reservationString, "000%d%d", tailReservationNumber, hotelRefNumber);
            break;

        case 4:
            sprintf(reservationString, "00%d%d", tailReservationNumber, hotelRefNumber);
            break;

        case 5:
            sprintf(reservationString, "0%d%d", tailReservationNumber, hotelRefNumber);
            break;

        case 6:
            sprintf(reservationString, "%d%d", tailReservationNumber, hotelRefNumber);
            break;

        default:
            break;
    }

    return reservationString;
}

char *transferStringToNode(char *input_string, char *destination)
{
    destination = (char *) malloc((strlen(input_string) + 1) * sizeof(char));

    if (destination == NULL)
    {
        abortProcess("\nWARNING MEMORY UNABLE TO BE ALLOCATED\n");
    }

    strcpy(destination, input_string);
    free(input_string);

    return destination;
}

void insertHotelNode(HOTEL *newHotelNode, HOTEL *left)
{
    if (alpha == NULL)
    {
        alpha = newHotelNode;
        return;
    }
    else
    {
        HOTEL *right;
        right = left->next;

        if (newHotelNode->hotelRefNumber < left->hotelRefNumber && alpha == left)
        {
            newHotelNode->next = left;
            alpha = newHotelNode;
            return;
        }

        if ((newHotelNode->hotelRefNumber > left->hotelRefNumber && right == NULL) || (newHotelNode->hotelRefNumber > left->hotelRefNumber && newHotelNode->hotelRefNumber < right->hotelRefNumber))
        {
            left->next = newHotelNode;
            newHotelNode->next = right;
            return;
        }
    }
    insertHotelNode(newHotelNode, left->next);
}

void reverseLinkedList(HOTEL *ptrToNode)
{
    if (ptrToNode->next == NULL)
    {
        alpha = ptrToNode;
        return;
    }

    reverseLinkedList(ptrToNode->next);
    ptrToNode->next->next = ptrToNode;
    ptrToNode->next = NULL;
}

void deleteHotelNode()
{
    char confirm = '\0';
    HOTEL *nodeDeleter = NULL, *addressLinker = NULL;
    RESERVATION *ptrToFreeReservationNode, *tempPtrForReservation;
    do
    {
        nodeDeleter = findHotelNode(nodeDeleter);
        printf("You have chosen:\n");
        printSpecificHotel(nodeDeleter);
        confirm = getUserConfirmation(confirm);
        printf("\n");
    }
    while (confirm == 'N' || confirm == 'n');

    if (nodeDeleter == alpha)
    {
        alpha = nodeDeleter->next;
    }
    else
    {
        addressLinker = alpha;
        while (addressLinker->next != nodeDeleter)
        {
            addressLinker = addressLinker->next;
        }
        addressLinker->next = nodeDeleter->next;
    }

    free(nodeDeleter->hotelName);
    ptrToFreeReservationNode = nodeDeleter->beta;
    while (ptrToFreeReservationNode != NULL)
    {
        tempPtrForReservation = ptrToFreeReservationNode->next;
        deleteSpecificReservationNode(&ptrToFreeReservationNode);
        ptrToFreeReservationNode = tempPtrForReservation;
    }
    free(nodeDeleter);
}

void deleteReservationNode()
{
    char confirm;
    struct getReturnValue HR;
    HR.ptrToHotelNode = NULL;
    HR.ptrToReservationNode = NULL;
    do
    {
        HR = findReservationNode();

        if (HR.ptrToHotelNode == NULL && HR.ptrToReservationNode == NULL)
        {
            return;
        }

        printf("You have chosen:\n");
        printSpecificReservation(HR.ptrToHotelNode, HR.ptrToReservationNode);
        confirm = getUserConfirmation(confirm);
    }
    while (confirm == 'N' || confirm == 'n');

    if (HR.ptrToReservationNode == HR.ptrToHotelNode->beta)
    {
        HR.ptrToHotelNode->beta = HR.ptrToReservationNode->next;
    }
    else
    {
        RESERVATION *addressLinker;
        addressLinker = HR.ptrToHotelNode->beta;
        while (addressLinker->next != HR.ptrToReservationNode)
        {
            addressLinker = addressLinker->next;
        }
        addressLinker->next = HR.ptrToReservationNode->next;
    }

    deleteSpecificReservationNode(&HR.ptrToReservationNode);

    HR.ptrToHotelNode->availableRooms++;
    return;
}

void deleteSpecificReservationNode(RESERVATION **freeReservationNode)
{
    free((*freeReservationNode)->reservationName);
    free((*freeReservationNode)->phoneNumber);
    free((*freeReservationNode)->mailAddress);
    free((*freeReservationNode));

    return;
}

void printLinkedList()
{
    HOTEL *ptrToHotelNode = alpha;

    if (ptrToHotelNode == NULL)
    {
        printf("<<<NO HOTEL LIST WAS FOUND>>>\n\n");
        return;
    }

    printf("Your Imaginary Hotel Chain:\n\n");
    for (ptrToHotelNode = alpha; ptrToHotelNode != NULL; ptrToHotelNode = ptrToHotelNode->next)
    {
        printSpecificHotel(ptrToHotelNode);
    }
}

void printReservationList()
{
    HOTEL *ptrToHotelNode;
    RESERVATION *ptrToReservationNode;

    int tripswitch = checkIfReservationEmpty(&ptrToHotelNode, &ptrToReservationNode);

    if (tripswitch == 1)
    {
        return;
    }

    printf("Your reservation list:\n\n");
    for (ptrToHotelNode = alpha; ptrToHotelNode != NULL; ptrToHotelNode = ptrToHotelNode->next)
    {
        ptrToReservationNode = ptrToHotelNode->beta;

        if (ptrToReservationNode == NULL)
        {
            printf("NO RESERVATION WAS FOUND FOR IMAGINARY HOTEL <%s>\n\n", ptrToHotelNode->hotelName);
        }
        else
        {
            for (ptrToReservationNode = ptrToHotelNode->beta; ptrToReservationNode != NULL; ptrToReservationNode = ptrToReservationNode->next)
            {
                printSpecificReservation(ptrToHotelNode, ptrToReservationNode);
            }
        }
    }

    return;
}

void printSpecificHotel(HOTEL *ptrToHotelNode)
{
    printf("No.%d IMAGINARY HOTEL <%s>\nStandard Price For 1 Night: ¥%d\nAvailable Rooms: %d\n\n", ptrToHotelNode->hotelRefNumber, ptrToHotelNode->hotelName, ptrToHotelNode->priceForNight, ptrToHotelNode->availableRooms);
    return;
}

void printSpecificReservation(HOTEL *ptrToHotelNode, RESERVATION *ptrToReservationNode)
{
    printf("No.%d IMAGINARY HOTEL <%s>\nCONFIRMATION NUMBER: %s    GUEST NAME: %s    TOTAL PRICE: ¥%d\nGUESTS: %d    NIGHTS OF STAY: %d NIGHTS    PHONE NUMBER: %s    EMAIL ADDRESS: %s\n\n", ptrToHotelNode->hotelRefNumber, ptrToHotelNode->hotelName, ptrToReservationNode->confirmationNumber, ptrToReservationNode->reservationName, ptrToReservationNode->totalPrice, ptrToReservationNode->numberOfGuests, ptrToReservationNode->nightsOfStay, ptrToReservationNode->phoneNumber, ptrToReservationNode->mailAddress);
    return;
}

void freeLinkedList()
{
    HOTEL *ptrToFreeHotelNode, *tempPtrForHotel;
    RESERVATION *ptrToFreeReservationNode, *tempPtrForReservation;
    ptrToFreeHotelNode = alpha;
    while (ptrToFreeHotelNode != NULL)
    {
        tempPtrForHotel = ptrToFreeHotelNode->next;
        free(ptrToFreeHotelNode->hotelName);
        ptrToFreeReservationNode = ptrToFreeHotelNode->beta;
        while (ptrToFreeReservationNode != NULL)
        {
            tempPtrForReservation = ptrToFreeReservationNode->next;
            deleteSpecificReservationNode(&ptrToFreeReservationNode);
            ptrToFreeReservationNode = tempPtrForReservation;
        }
        free(ptrToFreeHotelNode);
        ptrToFreeHotelNode = tempPtrForHotel;
    }

    return;
}

void abortProcess(const char *exitMessage)
{
    printf("%s", exitMessage);
    STORE_CSV_DATA(alpha);
    exit(EXIT_FAILURE);
}

int getReferenceNumberOfHotel(HOTEL **getCorrespondingHotelNode)
{
    int findRefNumber = getInt("Please select a hotel\nEnter the reference number to search---> ");

    if (findRefNumber > 999 || findRefNumber < 100)
    {
        printf("\n<<<A 3 DIGIT NUMBER MUST BE ENTERED>>>\nPLEASE TRY AGAIN\n\n");
        return 1;
    }
    else
    {
        (*getCorrespondingHotelNode) = alpha;
        while ((*getCorrespondingHotelNode)->hotelRefNumber != findRefNumber)
        {
            (*getCorrespondingHotelNode) = (*getCorrespondingHotelNode)->next;

            if ((*getCorrespondingHotelNode) == NULL)
            {
                printf("\n<<<WARNING A HOTEL HARBORING SUCH A REFERENCE NUMBER COULD NOT BE FOUND>>>\nPLEASE TRY AGAIN\n\n");
                return 1;
            }
        }
    }

    return 0;
}

HOTEL *findHotelNode(HOTEL *ptrToHotelNode)
{
    if (alpha == NULL)
    {
        printf("<<<NO HOTEL LIST DETECTED>>>");
        return ptrToHotelNode;
    }

    int alert;
    do
    {
        alert = 0;
        alert = getReferenceNumberOfHotel(&ptrToHotelNode);

        if (alert == 1)
        {
            printLinkedList();
        }
    }
    while (alert == 1);

    printf("\n");
    return ptrToHotelNode;
}

struct getReturnValue findReservationNode()
{
    struct getReturnValue HR;
    HR.ptrToHotelNode = NULL;
    HR.ptrToReservationNode = NULL;

    int tripswitch = checkIfReservationEmpty(&HR.ptrToHotelNode, &HR.ptrToReservationNode);

    if (tripswitch == 1)
    {
        return HR;
    }

    HOTEL *ptrToHotelNode = NULL;
    RESERVATION *ptrToReservationNode = NULL;
    int alert;
    do
    {
        alert = 0;
        char *findConfirmationNumber;
        do
        {
            alert = 0;
            findConfirmationNumber = getString("Please enter your confirmation number to search---> ");
            printf("\n");

            alert = findHotelNodeViaConfirmationNumber(&ptrToHotelNode, findConfirmationNumber);

            if (alert == 1)
            {
                printReservationList();
                free(findConfirmationNumber);
            }
        }
        while (alert == 1);

        ptrToReservationNode = ptrToHotelNode->beta;
        while (ptrToReservationNode != NULL)
        {
            if (strcmp(ptrToReservationNode->confirmationNumber, findConfirmationNumber) == 0)
            {
                HR.ptrToHotelNode = ptrToHotelNode;
                HR.ptrToReservationNode = ptrToReservationNode;
                free(findConfirmationNumber);
                return HR;
            }

            ptrToReservationNode = ptrToReservationNode->next;
        }

        if (ptrToReservationNode == NULL)
        {
            printf("<<<RESERVATION NOT FOUND>>>\nMAKE SURE THE CONFIRMATION NUMBER WAS INPUTTED CORRECTLY\nPLEASE TRY AGAIN\n\n");
            printReservationList();
            alert = 1;
        }

        free(findConfirmationNumber);
    }
    while (alert == 1);

    return HR;
}

int findHotelNodeViaConfirmationNumber(HOTEL **findCorrespondingHotelNode, char *findConfirmationNumber)
{
    int convertToInteger = 0;
    for (int i = 6; i < 9; i++)
    {
        convertToInteger = convertToInteger * 10 + findConfirmationNumber[i] - '0';
    }

    for ((*findCorrespondingHotelNode) = alpha; (*findCorrespondingHotelNode) != NULL; (*findCorrespondingHotelNode) = (*findCorrespondingHotelNode)->next)
    {
        if ((*findCorrespondingHotelNode)->hotelRefNumber == convertToInteger)
        {
            break;
        }
    }

    if ((*findCorrespondingHotelNode) == NULL)
    {
        printf("<<<CORRESPONDING HOTEL NOT FOUND>>>\n\n");
        return 1;
    }

    return 0;
}

int checkIfReservationEmpty(HOTEL **ptrToHotelNode, RESERVATION **ptrToReservationNode)
{
    if (alpha == NULL)
    {
        printf("<<<NO HOTEL LIST DETECTED>>>\n\n");
        return 1;
    }

    int reservationCount = 0;
    for ((*ptrToHotelNode) = alpha; (*ptrToHotelNode) != NULL; (*ptrToHotelNode) = (*ptrToHotelNode)->next)
    {
        (*ptrToReservationNode) = (*ptrToHotelNode)->beta;

        if ((*ptrToReservationNode) != NULL)
        {
            reservationCount++;
            break;
        }
    }

    if (reservationCount == 0)
    {
        printf("<<<NO RESERVATION WAS FOUND>>>\n\n");
        return 1;
    }

    return 0;
}

int READ_CSV_DATA()
{
    FILE *ptrToHotelFile = fopen("hotel_list.csv", "a+");
    FILE *ptrToReservationFile = fopen("reservation_list.csv", "a+");
    FILE *checkConfirmationNumber = fopen("confirmation_list.csv", "a+");

    if (checkConfirmationNumber == NULL)
    {
        abortProcess("NO STORAGE DIRECTORY FOR CONFIRMATION NUMBER FOUND");
    }

    int tailReservationNumber = 0;

    int c = fgetc(checkConfirmationNumber);

    if (c == EOF)
    {
        fprintf(checkConfirmationNumber, "%d\n", tailReservationNumber);
    }
    else
    {
        ungetc(c, checkConfirmationNumber);
    }

    fclose(checkConfirmationNumber);

    if (ptrToHotelFile == NULL)
    {
        printf("<<<NO STORAGE DIRECTORY FOUND>>>\n\n");
        fclose(ptrToReservationFile);
        fclose(ptrToHotelFile);
        return 1;
    }

    c = fgetc(ptrToHotelFile);

    if (c == EOF)
    {
        fclose(ptrToReservationFile);
        fclose(ptrToHotelFile);
        return 1;
    }
    else
    {
        ungetc(c, ptrToHotelFile);
    }

    int read = 0;
    do
    {
        HOTEL *ptrToHotelNode = (HOTEL *) calloc(1, sizeof(HOTEL));
        ptrToHotelNode->hotelName = (char *) malloc(1024 * sizeof(char));

        read = fscanf(ptrToHotelFile, "%d, %[^,], %d, %d\n", &ptrToHotelNode->hotelRefNumber, ptrToHotelNode->hotelName, &ptrToHotelNode->priceForNight, &ptrToHotelNode->totalRooms);

        if (read != 4)
        {
            printf("ITS NOT READING AT ALL WHY!\n\n");
            exit(EXIT_FAILURE);
        }

        ptrToHotelNode->hotelName = (char *) realloc(ptrToHotelNode->hotelName, (strlen(ptrToHotelNode->hotelName) + 1) * sizeof(char));
        ptrToHotelNode->availableRooms = ptrToHotelNode->totalRooms;
        insertHotelNode(ptrToHotelNode, alpha);
    }
    while (!feof(ptrToHotelFile));

    if (ptrToReservationFile == NULL)
    {
        printf("<<<NO STORAGE DIRECTORY FOR RESERVATION FOUND>>>\n\n");
        fclose(ptrToReservationFile);
        fclose(ptrToHotelFile);
        return 0;
    }

    c = fgetc(ptrToReservationFile);

    if (c == EOF)
    {
        fclose(ptrToReservationFile);
        fclose(ptrToHotelFile);
        return 0;
    }
    else
    {
        ungetc(c, ptrToReservationFile);
    }

    HOTEL *findCorrespondingHotelNode;
    RESERVATION *ptrToReservationNode;
    do
    {
        int findRefNode = 0;
        findCorrespondingHotelNode = NULL;
        ptrToReservationNode = (RESERVATION *) calloc(1, sizeof(RESERVATION));
        ptrToReservationNode->reservationName = (char *) malloc(1024 * sizeof(char));
        ptrToReservationNode->phoneNumber = (char *) malloc(1024 * sizeof(char));
        ptrToReservationNode->mailAddress = (char *) malloc(1024 * sizeof(char));

        read = fscanf(ptrToReservationFile, "%[^,], %[^,], %[^,], %[^,], %d, %d, %d\n", ptrToReservationNode->confirmationNumber, ptrToReservationNode->reservationName, ptrToReservationNode->phoneNumber, ptrToReservationNode->mailAddress, &ptrToReservationNode->numberOfGuests, &ptrToReservationNode->nightsOfStay, &ptrToReservationNode->totalPrice);

        if (read != 7)
        {
            printf("GOD HAS ABONDONED HIS CREATIONS\n\n");
            exit(EXIT_FAILURE);
        }

        ptrToReservationNode->reservationName = (char *) realloc(ptrToReservationNode->reservationName, (strlen(ptrToReservationNode->reservationName) + 1) * sizeof(char));
        ptrToReservationNode->phoneNumber = (char *) realloc(ptrToReservationNode->phoneNumber, (strlen(ptrToReservationNode->phoneNumber) + 1) * sizeof(char));
        ptrToReservationNode->mailAddress = (char *) realloc(ptrToReservationNode->mailAddress, (strlen(ptrToReservationNode->mailAddress) + 1) * sizeof(char));

        findHotelNodeViaConfirmationNumber(&findCorrespondingHotelNode, ptrToReservationNode->confirmationNumber);

        if (findCorrespondingHotelNode == NULL)
        {
            printf("\n<<<WARNING CRITICAL FORMATTING ERROR DETECTED>>>\nSHUTTING DOWN...\n\n");
            exit(EXIT_FAILURE);
        }

        if (findCorrespondingHotelNode->beta == NULL)
        {
            findCorrespondingHotelNode->beta = ptrToReservationNode;
        }
        else
        {
            ptrToReservationNode->next = findCorrespondingHotelNode->beta;
            findCorrespondingHotelNode->beta = ptrToReservationNode;
        }

        findCorrespondingHotelNode->availableRooms--;
    }
    while (!feof(ptrToReservationFile));

    fclose(ptrToReservationFile);
    fclose(ptrToHotelFile);

    return 0;
}

void STORE_CSV_DATA(HOTEL *storeHotelIntoFile)
{
    FILE *ptrToHotelFile = fopen("hotel_list.csv", "w");
    FILE *ptrToReservationFile = fopen("reservation_list.csv", "w");

    if (!ptrToHotelFile || !ptrToReservationFile)
    {
        printf("<<<NO STORAGE DIRECTORY FOUND>>>\nCREATING NEW FILE\n\n");
    }

    HOTEL *tempPtrToHotel;
    RESERVATION *storeReservationIntoFile, *previousReservationNode;
    while (storeHotelIntoFile != NULL)
    {
        fprintf(ptrToHotelFile, "%d, %s, %d, %d\n", storeHotelIntoFile->hotelRefNumber, storeHotelIntoFile->hotelName, storeHotelIntoFile->priceForNight, storeHotelIntoFile->totalRooms);
        while (storeHotelIntoFile->beta != NULL)
        {
            storeReservationIntoFile = storeHotelIntoFile->beta;
            while (storeReservationIntoFile->next != NULL)
            {
                previousReservationNode = storeReservationIntoFile;
                storeReservationIntoFile = storeReservationIntoFile->next;
            }

            if (storeReservationIntoFile == storeHotelIntoFile->beta)
            {
                storeHotelIntoFile->beta = NULL;
            }
            else
            {
                previousReservationNode->next = NULL;
            }

            fprintf(ptrToReservationFile, "%s, %s, %s, %s, %d, %d, %d\n", storeReservationIntoFile->confirmationNumber, storeReservationIntoFile->reservationName, storeReservationIntoFile->phoneNumber, storeReservationIntoFile->mailAddress, storeReservationIntoFile->numberOfGuests, storeReservationIntoFile->nightsOfStay, storeReservationIntoFile->totalPrice);
            deleteSpecificReservationNode(&storeReservationIntoFile);
        }

        tempPtrToHotel = storeHotelIntoFile->next;
        free(storeHotelIntoFile->hotelName);
        free(storeHotelIntoFile);
        storeHotelIntoFile = tempPtrToHotel;
    }

    fclose(ptrToReservationFile);
    fclose(ptrToHotelFile);
}
