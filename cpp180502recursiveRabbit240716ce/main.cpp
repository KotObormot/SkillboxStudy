#include <iostream>

int rabbit_jumping(int targetPosition, int maxJumpLength = 3) {
	int numberOfAttempts = 0;

	if(targetPosition == 0) {
		return 1;
	}
	
	for(int jumpsLength = 1; jumpsLength <= std::min(targetPosition, maxJumpLength); jumpsLength++) {
		numberOfAttempts += rabbit_jumping(targetPosition - jumpsLength, maxJumpLength);
	}

	return numberOfAttempts;
}

int main() {
	int n, k; 
	
	do {
	    std::cout << "Which step does the bunny want to jump to? (> 0) --> ";
	    std::cin >> n;
    }
	while(n <= 0);
	
	std::cout << "The default bunny hop length is 3. Would you like to enter a different value? (> 0) --> ";
	std::cin >> k;
	
	std::cout << "Let's calculate...\n======================================\n";
	std::cout << "The rabbit will be able to jump in ";
	if(k > 0) {
        std::cout << rabbit_jumping(n, k);
    } else {
	    std::cout << rabbit_jumping(n);		
	}	 
 	std::cout << " attempts.\n";	
}
