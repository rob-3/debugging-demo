#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define STR_LEN 20
#define HOTEL_SIZE 17

typedef struct Guest {
	char name[STR_LEN];
	int phone;
} Guest;

typedef struct Hotel {
	// Array of Guest*
	Guest **occupants;
	int size;
} Hotel;

/**
 * @param filename path to file with guest data
 * @param len_out out param for length of both arrays
 * @param rms_out out array of room numbers
 * @return array of Guests read from file
 */
Guest* read_guests(char *filename, int *len_out, int **rms_out) {
	FILE *ifp = fopen(filename, "r");

	int len;
	fscanf(ifp, "%d", &len);
	Guest *guests = malloc(sizeof(Guest) * HOTEL_SIZE);
	*rms_out = malloc(sizeof(int) * len);
	for (int i = 0; i < len; i++) {
		char name[STR_LEN]; 
		int phone;
		int room_number;
		fscanf(ifp, "%s", name);
		fscanf(ifp, "%d", &phone);
		fscanf(ifp, "%d", &room_number);
		strcpy(guests[i].name, name);
		guests[i].phone = phone;
		// dereference pointer to array and then add the correct room number
		(*rms_out)[i] = room_number;
	}
	fclose(ifp);
	*len_out = len;
	return guests;
}

/**
 * @param size total size of hotel
 * @return initialized hotel struct
 */
Hotel* make_hotel(int size) {
	Hotel *hotel = malloc(sizeof(Hotel));
	hotel->occupants = malloc(sizeof(Guest*) * size);
	hotel->size = size;
	for (int i = 0; i < size i++) {
		hotel->occupants[i] = NULL;
	}
	return hotel;
}

/**
 * Prints floor and name of occupants.
 * @param hotel Hotel to print
 */
void print_hotel(Hotel *hotel) {
	for (int i = 0; i < hotel->size; i++) {
		Guest *g = hotel->occupants[i];
		if (g != NULL) {
			printf("Room %d\t%s\n", i + 1, g->name);
		}
	}
}

/**
 * Prompts user for guest info.
 * @param room_number out param for room number
 * @return newly created Guest
 */
Guest make_guest(int *room_number) {
	char name[STR_LEN];
	int phone;
	printf("Guest name: ");
	scanf("%s", name);
	printf("Guest phone: ");
	scanf("%d", &phone);
	printf("Guest room number: ");
	scanf("%d", room_number);

	Guest g;
	strcpy(g.name, name);
	g.phone = phone;
	return g;
}

/**
 * Checks in a new guest or returns a nonzero error code.
 * @param guest Guest to check in
 * @param hotel Hotel to check in guest
 * @param room_number Room to check in guest
 * @return 0 if successful, 1 if room already occupied, 2 if room doesn't exist
 */
int check_in(Guest *guest, Hotel *hotel, int room_number) {
	if (room_number > hotel->size || room_number <= 0) return 2;
	if (hotel->occupants[room_number - 1] != NULL) return 1;
	hotel->occupants[room_number - 1] = guest;
	return 0;
}

/**
 * Checks out a guest or returns a nonzero error code.
 * @param hotel Hotel to check out guest
 * @param room_number Room to check out
 * @return 0 if successful, 1 if room already unoccupied, 2 if room doesn't exist
 */
int check_out(Hotel *hotel, int room_number) {
	if (room_number > hotel->size || room_number <= 0) return 2;
	if (hotel->occupants[room_number] == NULL) return 1;
	hotel->occupants[room_number] = NULL;
	return 0;
}

void print_guest(Guest *g) {
	printf("\nName: %s\nPhone: %d\n", g->name, g->phone);
}

int room_prompt() {
	int room;	
	printf("Which room?\n");
	printf("> ");
	scanf("%d", &room);
	return room;
}

/**
 * Persist hotel data to file.
 * @param hotel Hotel to persist
 * @param filename file to write to
 */
void save_hotel(Hotel *hotel, char *filename) {
	FILE *ofp = fopen(filename, "w");
	int count = 0;
	for (int i = 0; i < hotel->size; i++) {
		Guest *g = hotel->occupants[i];
		if (g != NULL) {
			count++;
		}
	}
	fprintf(ofp, "%d\n", count);
	for (int i = 0; i < hotel->size; i++) {
		Guest *g = hotel->occupants[i];
		if (g != NULL) {
			fprintf(ofp, "%s\t%d\t%d\n", g->name, g->phone, i + 1);
		}
	}
}

int main(void) {
	Hotel *hotel = make_hotel(HOTEL_SIZE);

	int len;
	int *room_numbers = NULL;
	Guest *guests = read_guests("hotel.txt", &len, &room_numbers);

	for (int i = 0; i < len; i++) {
		hotel->occupants[room_numbers[i] - 1] = &guests[i];
	}

	int choice;
	do {
		printf("\n");
		print_hotel(hotel);
		printf("\n");
		printf("1) Check in\n");
		printf("2) Check out\n");
		printf("3) Guest info\n");
		printf("4) Exit\n");
		printf("> ");
		scanf("%d", &choice);
		int room;
		Guest g;
		switch(choice) {
			case 1:
				g = make_guest(&room);
				guests[len] = g;
				len++;
				switch(check_in(&guests[len - 1], hotel, room)) {
					case 0:
						printf("\nGuest checked in.\n");
						break;
					case 1:
						printf("\nRoom already occupied.\n");
						break;
					case 2:
						printf("\nNo such room.\n");
						break;
				}
				break;
			case 2:
				switch(check_out(hotel, room_prompt())) {
					case 0:
						printf("\nGuest checked out.\n");
						break;
					case 1:
						printf("\nRoom already empty.\n");
						break;
					case 2:
						printf("\nNo such room.\n");
						break;
				}
				break;
			case 3:
				room = room_prompt();
				if (hotel->occupants[room - 1] == NULL) {
					printf("\nThere is no one in that room.\n");
				} else {
					print_guest(hotel->occupants[room - 1]);
				}
				break;
			case 4:
				save_hotel(hotel, "hotel.txt");
				break;
			default:
				printf("\nInvalid choice! Please try again.\n");
		}
	} while (choice != 4);

	free(guests);
	free(room_numbers);
	free(hotel->occupants);
	free(hotel);
	return 0;
}
