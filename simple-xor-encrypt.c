/*

		Simple XOR encryption using pre-defined static (hard-coded) private key.

		Reads string from text file (also, static / hard-coded) and then encrypts plaintext / decrypts the ciphertext back to original plaintext.

*/
#define _GNU_SOURCE

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

void xor_encrypt(char *input, const char *key)
{
	size_t input_len = strlen(input);
	size_t key_len = strlen(key); // get the length of the key

	for (size_t i = 0; i < input_len; i++)
	{
		input[i] = input[i] ^ key[i % key_len];
	}
}

int main()
{
	// define the private key to use for XOR encryption
	const char key[] = "<<<REPLACE THIS KEY WITH YOUR PRIVATE KEY>>>";

	// define the text file to extract the plaintext from
	const char filename[] = "./plaintext.txt";

	// open text file
	FILE *fp = fopen(filename, "r"); // open the file for reading
	printf("\nOpening the input file: %s\n", filename);
	printf("\nExpecting %s to have a single line of text:\n"
				 "First Name + Surname.\n"
				 "e.g. Bryan Johnston.\n",
				 filename);

	// check if the file exists
	if (fp == NULL)
	{
		printf("Error opening the input file: %d\n", errno);
		perror("Error message");
		exit(EXIT_FAILURE);
	}

	/* getline is not compatible in Windows -- replaced with fgets but it is an alternative method */
	// char *line = NULL;
	// size_t len = 0;
	// getline(&line, &len, fp);

	char line[30] = "";	 // declare a char array to store the string
	fgets(line, 30, fp); // read the line from the file
	fclose(fp);					 // close the file

	// Check that the desired input exists
	if (line == NULL)
	{
		printf("The input file is empty.\n");
	}
	else
	{
		printf("\n"
					 "The line read from the input file is: \n"
					 "%s"
					 "\n",
					 line);
	}

	// Encrypt the plaintext using XOR
	printf("Encrypting...\n");
	xor_encrypt(line, key);

	// Display the encrypted text
	printf("Encrypted Text: %s\n", line);

	printf("\nEncrypted Text as numbers: \n");
	// Print ciphertext as numbers
	for (int i = 0; i < strlen(line); i++)
	{
		printf("%d", line[i]);
	}
	printf("\n\n");

	// Decrypt the ciphertext (since XOR is symmetric, encrypting again decrypts)
	printf("Decrypting...\n");
	xor_encrypt(line, key);

	// Display the decrypted text
	printf("\nDecrypted Text: %s\n", line);

	// free(line);
	return 0;
}
