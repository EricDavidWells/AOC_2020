#include<iostream>



int loop_once(long long& accum, long& subject_number, long& loop_count) {

	loop_count++;
	return (accum * subject_number) % 20201227;
}

int main() {



	long card_public_key = 2084668;
	long door_public_key = 3704642;

	//long card_public_key = 5764801;
	//long door_public_key = 17807724;

	long subject_number = 7;

	long long card_accum = 1;
	long long door_accum = 1;
	bool card_flag = false;
	bool door_flag = false;

	long card_loop_size = 0;
	long door_loop_size = 0;

	while (!card_flag || !door_flag) {

		if (card_accum != card_public_key) {
			card_accum = loop_once(card_accum, subject_number, card_loop_size);
		}
		else {
			card_flag = true;
		}

		if (door_accum != door_public_key) {
			door_accum = loop_once(door_accum, subject_number, door_loop_size);
		}
		else {
			door_flag = true;
		}
	}

	long long encrypt_accum = 1;
	long encrypt_loop_size = 0;
	while (encrypt_loop_size < card_loop_size) {
		encrypt_accum = loop_once(encrypt_accum, door_public_key, encrypt_loop_size);
	}


	std::cout << encrypt_accum << std::endl;

	return 0;
}