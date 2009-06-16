/*
 * $Id$
 * -----------------------
 * The distributed dbook thing
 */

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <strings.h>
#include "libdbook.h"

/*
 * XXX
 * This is not used just yet, is carston still hacking this?
 * This is C++ !!!!!!!!!!!!!!!!!!!!!!!!!!
 * The library should all be pure C99!
 */

int dbook_connect_send_wait_receive(void* input) {
    int sockfd;
    int portno;
    int n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char buffer[512];

    if (argc < 2) {
        cout << "Error: No host specified" << endl;
        return 1;
    }

    if (argc < 3) {
        cout << "Error: No port specified" << endl;
        return 1;
    }

    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if(sockfd < 0) {
        cout << "Error: Could not open socket" << endl;
        return 1;
    }

    server = gethostbyname(argv[1]);

    if(server == NULL) {
        cout << "Error: Could not find host" << endl;
        return 1;
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,
            (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);

    if (connect(sockfd, (const sockaddr*)&serv_addr,
                sizeof(serv_addr)) < 0) {
        cout << "Error: Could not connect" << endl;
        return 1;
    }

    printf("Please enter the message: ");
    bzero(buffer, 512);
    fgets(buffer, 511, stdin);
    n = write(sockfd,buffer,strlen(buffer));

    if (n < 0) {
        cout << "Error: Could not write to socket" << endl;
        return 1;
    }

    bzero(buffer, 512);
    n = read(sockfd, buffer, 511);

    if(n < 0) {
        cout << "Error: Could not read from socket" << endl;
        return 1;
    }

    cout << "Received: " << n << " bytes" << endl;
    cout << "Message: " << buffer << endl;

    return 0;
}

/** 
  Returns the checksum for a ISBN 10 passed in as paramter
  */
char dbook_gen_chksum_10_dis(DBOOK_ISBN *isbnToTest) {
    return 'X';
}


/** 
  Returns the checksum for a ISBN 13 passed in as paramter
  */
char dbook_gen_chkSum_13_dis(DBOOK_ISBN *isbnToTest) {
    return 'X';
}

int dbook_check_isbn_dis(DBOOK_ISBN *isbnToCheck) {
    return DBOOK_FALSE;
}

int dbook_isbn_10_to_13_dis(DBOOK_ISBN *from, DBOOK_ISBN *to) {
    return DBOOK_FALSE;
}

int dbook_isbn_13_to_10_dis(DBOOK_ISBN *from, DBOOK_ISBN *to) {
    return DBOOK_FALSE;
}

/**
 * Removes all the rubbish that is normally in an isbn like - and spaces
 * first value is a char * to be cleaned
 * second is a dbook_isbn for the clean isbn to be put in
 */ 
int dbook_sanitize_dis(char *from, DBOOK_ISBN *to) {
    return DBOOK_FALSE;
}

int dbook_get_isbn_details_dis(DBOOK_ISBN *whichBook, dbook_book *book) {
    return DBOOK_FALSE;
}

/**
 * Checks if the isbn is a isbn 13. Does not validate only takes the length
 */
int dbook_is_isbn_13_dis(DBOOK_ISBN *isbnToCheck) {
    return DBOOK_FALSE;
}

/**
 * Checks if the isbn is a isbn 10. Does not validate only takes the length
 */
int dbook_is_isbn_10_dis(DBOOK_ISBN *isbnToCheck) {
    return DBOOK_FALSE; 
}

