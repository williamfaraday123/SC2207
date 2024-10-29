#include <stdio.h>
#include <string.h>

// d is the number of characters in the input alphabet
#define d 256

/* pat -> pattern
	txt -> text
	q -> A prime number
*/

int hash(char str[], int length, int d, int q) 
{
  int hash_val = 0;
  for (int i = 0; i < length; i++) {
    hash_val = (d * hash_val + str[i]) % q;
  }
  return hash_val;
}
int equal_string(char pat[], char txt[], int txtStartIndex, int patLength)
{
  int i;
  /* Check for characters one by one */
  for (i = 0; i < patLength; i++) {
    if (txt[txtStartIndex + i] != pat[i])
      break;
  }
  if (i == patLength)
    return 1;
  return 0;
}
int rehash(char txt[], int i, int patLength, int ht, int q, int dM)
{
  // Calculate hash value for next window of text:
	// Remove leading digit, add trailing digit
  int new_hash_val = (d * (ht - txt[i] * dM) + txt[i + patLength]) % q;

  // We might get negative value of ht, converting it to positive
  if (new_hash_val < 0)
    new_hash_val = new_hash_val + q;
  
  return new_hash_val;
}
void RabinKarpScan(char pat[], char txt[], int q)
{
	int M = strlen(pat);
	int N = strlen(txt);
	int i;
	int dM = 1;

	// The value of dM would be "pow(d, M-1)%q"
	for (i = 0; i < M - 1; i++)
		dM = (dM * d) % q;

	// Calculate the hash value of pattern and first window of text
  int hp = hash(pat, M, d, q);  // hash value for pattern
  int ht = hash(txt, M, d, q);  // hash value for first window of txt

	// Slide the pattern over text one by one
	for (i = 0; i <= N - M; i++) {

		// Check the hash values of current window of text
		// and pattern. If the hash values match then only
		// check for characters one by one
		if (hp == ht && equal_string(pat, txt, i, M)) {
				return i; //Pattern found at index i
		}

		// Calculate hash value for next window of text:
		// Remove leading digit, add trailing digit
		if (i < N - M) {
			ht = rehash(txt, i, M, ht, q, dM);
		}
	}

  return -1; //pattern not found
}

/*
Time complexity:
-  N - M + 1 iterations of for loop
-  equal_string(pat, txt, i, M) takes O(M) time
-  Overall time complexity = O((N - M + 1) * M)
*/
