// AVL tree implementation in C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
struct Node {
	char song_name[100];
    char singer[100];
    char lyricist[100];
    char album[100];
    char composer[100];
    char genre[100];
    int duration;
    int flag;
    int index;
    int height;
    struct Node* left;
    struct Node* right;
};

// Create Node
//struct Node {
//  int key;
//  struct Node *left;
//  struct Node *right;
//  int height;
//};

int max(int a, int b);

// Calculate height
int height(struct Node *N) {
  if (N == NULL)
    return 0;
  return N->height;
}

int max(int a, int b) {
  return (a > b) ? a : b;
}

// Create a node
struct Node *newNode(char* song_name,char* singer,char* lyricist,char* album,char* composer,char* genre,int duration) {
	
  struct Node *node = (struct Node *)malloc(sizeof(struct Node));
  	strcpy(node->song_name,song_name);
	strcpy(node->singer,singer);
	strcpy(node->lyricist,lyricist);
	strcpy(node->album,album);
	strcpy(node->composer,composer);
	strcpy(node->genre,genre);
	node->duration=duration;
  node->left = NULL;
  node->right = NULL;
  node->height = 1;
  return (node);
}

// Right rotate
struct Node *rightRotate(struct Node *y) {
  struct Node *x = y->left;
  struct Node *T2 = x->right;

  x->right = y;
  y->left = T2;

  y->height = max(height(y->left), height(y->right)) + 1;
  x->height = max(height(x->left), height(x->right)) + 1;

  return x;
}

// Left rotate
struct Node *leftRotate(struct Node *x) {
  struct Node *y = x->right;
  struct Node *T2 = y->left;

  y->left = x;
  x->right = T2;

  x->height = max(height(x->left), height(x->right)) + 1;
  y->height = max(height(y->left), height(y->right)) + 1;

  return y;
}

// Get the balance factor
int getBalance(struct Node *N) {
  if (N == NULL)
    return 0;
  return height(N->left) - height(N->right);
}

struct Node *lptr = NULL;

// Insert node
struct Node *insertNode(struct Node *root, char* song_name,char* singer,char* lyricist,char* album,char* composer,char* genre,int duration) {
  // Find the correct position to insertNode the node and insertNode it
  if (root == NULL)
    return (newNode(song_name,singer,lyricist,album,composer,genre,duration));

  if (strcmp(song_name,root->song_name)<0)
    root->left = insertNode(root->left,song_name,singer,lyricist,album,composer,genre,duration);
  else if (strcmp(song_name,root->song_name)>0)
    root->right = insertNode(root->right,song_name,singer,lyricist,album,composer,genre,duration);
  else
    return root;

  // Update the balance factor of each node and
  // Balance the tree
  root->height = 1 + max(height(root->left),
               height(root->right));

  int balance = getBalance(root);
  if (balance > 1 && strcmp(song_name,root->left->song_name)<0)
    return rightRotate(root);

  if (balance < -1 && strcmp(song_name,root->right->song_name)>0)
    return leftRotate(root);

  if (balance > 1 && strcmp(song_name,root->left->song_name)>0) {
    root->left = leftRotate(root->left);
    return rightRotate(root);
  }

  if (balance < -1 && strcmp(song_name,root->right->song_name)<0) {
    root->right = rightRotate(root->right);
    return leftRotate(root);
  }

  return root;
}


struct Node *root11 = NULL;

struct Node *insertNode11(struct Node *root, char* song_name,char* singer,char* lyricist,char* album,char* composer,char* genre,int duration) {
  // Find the correct position to insertNode the node and insertNode it
  if (root == NULL)
    return (newNode(song_name,singer,lyricist,album,composer,genre,duration));

  if (strcmp(singer,root->singer)<0)
    root->left = insertNode11(root->left,song_name,singer,lyricist,album,composer,genre,duration);
  else if (strcmp(singer,root->singer)>0)
    root->right = insertNode11(root->right,song_name,singer,lyricist,album,composer,genre,duration);
  else
    return root;

  // Update the balance factor of each node and
  // Balance the tree
  root->height = 1 + max(height(root->left),
               height(root->right));

  int balance = getBalance(root);
  if (balance > 1 && strcmp(singer,root->left->singer)<0)
    return rightRotate(root);

  if (balance < -1 && strcmp(singer,root->right->singer)>0)
    return leftRotate(root);

  if (balance > 1 && strcmp(singer,root->left->singer)>0) {
    root->left = leftRotate(root->left);
    return rightRotate(root);
  }

  if (balance < -1 && strcmp(singer,root->right->singer)<0) {
    root->right = rightRotate(root->right);
    return leftRotate(root);
  }

  return root;
}

bool insideRange=false;

void q11(struct Node* root, char *first, char* second){
	

	if(root==NULL)return;
	else if(strcmp(root->singer,first)<0&&strcmp(root->singer,second)<0){
		q11(root->right,first,second);
	}
	else if(strcmp(root->singer,first)>0&&strcmp(root->singer,second)>0){
		q11(root->left,first,second);
	}
	else{
		q11(root->left,first,second);
		printf("Song: %s\n", root->song_name);
		printf("Singer: %s\n", root->singer);
	    printf("Lyricist: %s\n", root->lyricist);
	    printf("Album/Film: %s\n", root->album);
	    printf("Composer: %s\n", root->composer);
	    printf("Genre: %s\n", root->genre);
	    printf("Duration: %d seconds\n", root->duration);
	    q11(root->right,first,second);
	}
}



struct Node *minValueNode(struct Node *node) {
  struct Node *current = node;

  while (current->left != NULL)
    current = current->left;

  return current;
}

// Delete a nodes
struct Node *deleteNode(struct Node *root, char* song_name) {
  // Find the node and delete it
  if (root == NULL)
    return root;

  if (strcmp(song_name,root->song_name)<0)
    root->left = deleteNode(root->left,song_name);

  else if (strcmp(song_name,root->song_name)>0)
    root->right = deleteNode(root->right,song_name);

  else {
    if ((root->left == NULL) || (root->right == NULL)) {
      struct Node *temp = root->left ? root->left : root->right;

      if (temp == NULL) {
        temp = root;
        root = NULL;
      } else
        *root = *temp;
      free(temp);
    } else {
      struct Node *temp = minValueNode(root->right);

      strcpy(root->song_name,temp->song_name);
	strcpy(root->singer,temp->singer);
	strcpy(root->lyricist,temp->lyricist);
	strcpy(root->album,temp->album);
	strcpy(root->composer,temp->composer);
	strcpy(root->genre,temp->genre);
	  ///------------------------------------
      /*
      char song_name[100];
    char singer[100];
    char lyricist[100];
    char album[100];
    char composer[100];
    char genre[100];
    int duration;
    int flag;
    int index;
    int height;
      */

      root->right = deleteNode(root->right, temp->song_name);
    }
  }

  if (root == NULL)
    return root;

  // Update the balance factor of each node and
  // balance the tree
  root->height = 1 + max(height(root->left),
               height(root->right));

  int balance = getBalance(root);
  if (balance > 1 && getBalance(root->left) >= 0)
    return rightRotate(root);

  if (balance > 1 && getBalance(root->left) < 0) {
    root->left = leftRotate(root->left);
    return rightRotate(root);
  }

  if (balance < -1 && getBalance(root->right) <= 0)
    return leftRotate(root);

  if (balance < -1 && getBalance(root->right) > 0) {
    root->right = rightRotate(root->right);
    return leftRotate(root);
  }

  return root;
}

// Print the tree
void printInOrderwithout(struct Node *root) {
  if (root != NULL) {
  	printInOrderwithout(root->left);
    printf("Song: %s\n", root->song_name);
	printf("Singer: %s\n", root->singer);
    printf("Lyricist: %s\n", root->lyricist);
    printf("Album/Film: %s\n", root->album);
    printf("Composer: %s\n", root->composer);
    printf("Genre: %s\n", root->genre);
    printf("Duration: %d seconds\n", root->duration);
    printInOrderwithout(root->right);
  }
}
void printInOrderDash(struct Node *root) {
  if (root != NULL) {
  	printInOrderDash(root->right);
    printf("Song: %s\n", root->song_name);
	printf("Singer: %s\n", root->singer);
    printf("Lyricist: %s\n", root->lyricist);
    printf("Album/Film: %s\n", root->album);
    printf("Composer: %s\n", root->composer);
    printf("Genre: %s\n", root->genre);
    printf("Duration: %d seconds\n", root->duration);
    printInOrderDash(root->left);
  }
}
//----------------------------------------------------------------------------------------------------------------------

int countinQ10;


struct Node *deleteSong(struct Node *root, char* song_name) {
  // Find the node and delete it
  if (root == NULL)
    return root;

  if (strcmp(song_name,root->song_name)<0)
    root->left = deleteSong(root->left,song_name);

  else if (strcmp(song_name,root->song_name)>0)
    root->right = deleteSong(root->right,song_name);

  else {
    if ((root->left == NULL) || (root->right == NULL)) {
      struct Node *temp = root->left ? root->left : root->right;

      if (temp == NULL) {
        temp = root;
        root = NULL;
      } else
        *root = *temp;
      free(temp);
    } else {
      struct Node *temp = minValueNode(root->right);

      strcpy(root->song_name,temp->song_name);
	strcpy(root->singer,temp->singer);
	strcpy(root->lyricist,temp->lyricist);
	strcpy(root->album,temp->album);
	strcpy(root->composer,temp->composer);
	strcpy(root->genre,temp->genre);
	  ///------------------------------------
      /*
      char song_name[100];
    char singer[100];
    char lyricist[100];
    char album[100];
    char composer[100];
    char genre[100];
    int duration;
    int flag;
    int index;
    int height;
      */

      root->right = deleteSong(root->right, temp->song_name);
    }
  }

  if (root == NULL)
    return root;

  // Update the balance factor of each node and
  // balance the tree
  root->height = 1 + max(height(root->left),
               height(root->right));

  int balance = getBalance(root);
  if (balance > 1 && getBalance(root->left) >= 0)
    return rightRotate(root);

  if (balance > 1 && getBalance(root->left) < 0) {
    root->left = leftRotate(root->left);
    return rightRotate(root);
  }

  if (balance < -1 && getBalance(root->right) <= 0)
    return leftRotate(root);

  if (balance < -1 && getBalance(root->right) > 0) {
    root->right = rightRotate(root->right);
    return leftRotate(root);
  }

  return root;
}


struct Node *deleteArtist(struct Node *root, char* song_name) {
  // Find the node and delete it
    if (root == NULL)
        return root;

    root->left = deleteArtist(root->left,song_name);

    root->right = deleteArtist(root->right,song_name);

    if(strcmp(root->singer,song_name)==0){

        if ((root->left == NULL) || (root->right == NULL)) {

            struct Node *temp = root->left ? root->left : root->right;

                if (temp == NULL) {
                        temp = root;
                        root = NULL;
                } else{
                    *root = *temp;
                }
                free(temp);
            

        } 
            
        else {

            struct Node *temp = minValueNode(root->right);

            strcpy(root->song_name,temp->song_name);
            strcpy(root->singer,temp->singer);
            strcpy(root->lyricist,temp->lyricist);
            strcpy(root->album,temp->album);
            strcpy(root->composer,temp->composer);
            strcpy(root->genre,temp->genre);
            ///------------------------------------
            /*
            char song_name[100];
            char singer[100];
            char lyricist[100];
            char album[100];
            char composer[100];
            char genre[100];
            int duration;
            int flag;
            int index;
            int height;
            */

            root->right = deleteArtist(root->right, temp->song_name);
        }

        if (root == NULL)
            return root;

        // Update the balance factor of each node and
        // balance the tree
        root->height = 1 + max(height(root->left),
                    height(root->right));

        int balance = getBalance(root);
        if (balance > 1 && getBalance(root->left) >= 0)
            return rightRotate(root);

        if (balance > 1 && getBalance(root->left) < 0) {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }

        if (balance < -1 && getBalance(root->right) <= 0)
            return leftRotate(root);

        if (balance < -1 && getBalance(root->right) > 0) {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
    }

  return root;
}

void playlist(struct Node *root,struct Node input_att){
	
	struct Node *cur = root;
//	lptr = NULL;

    if(root==NULL){
        return;
    }

    if(root->left){
        playlist(root->left,input_att);
    }
    	
        if((strcmp(input_att.song_name,"#")==0 || strcmp(input_att.song_name,cur->song_name)==0)&& 
        (strcmp(input_att.singer,"#")==0 || strcmp(input_att.singer,cur->singer)==0) &&
        (strcmp(input_att.lyricist,"#")==0 || strcmp(input_att.lyricist,cur->lyricist)==0) &&
        (strcmp(input_att.album,"#")==0 || strcmp(input_att.album,cur->album)==0) &&
        (strcmp(input_att.composer,"#")==0 || strcmp(input_att.composer,cur->composer)==0) &&
        (strcmp(input_att.genre,"#")==0 || strcmp(input_att.genre,cur->genre)==0)
        ){
            lptr = insertNode(lptr,cur->song_name,cur->singer,cur->lyricist,cur->album,cur->composer,cur->genre,cur->duration);
            countinQ10++;
        }
    if(root->right){
        playlist(root->right,input_att);
    }

}






void createPlaylist(struct Node *root){
	
	struct Node input_att;
    strcpy(input_att.album,"#");
    strcpy(input_att.composer,"#");
    strcpy(input_att.genre,"#");
    strcpy(input_att.lyricist,"#");
    strcpy(input_att.singer,"#");
    strcpy(input_att.song_name,"#");
	int choice;
    do {
        printf("\nCreate a play-list based on the attribute\n"); //update
        printf("1. song_name\n");
        printf("2. singer\n");
        printf("3. lyricist\n");
        printf("4. album\n");
        printf("5. composer\n");
        printf("6. genre\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter song name: ");
                scanf("%s", input_att.song_name);
                break;
            case 2:
                printf("Enter singer name: ");
                scanf("%s", input_att.singer);
                break;
            case 3:
                printf("Enter lyricist name: ");
                scanf("%s", input_att.lyricist);
                break;
            case 4:
                printf("Enter album/film name: ");
                scanf("%s", input_att.album);
                break;
            case 5:
                printf("Enter composer name: ");
                scanf("%s", input_att.composer);
                break;
            case 6:
                printf("Enter genre: ");
                scanf("%s", input_att.genre);
                break;
            case 0:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice, please try again.\n");
        }
    } while (choice != 0);

    
    playlist(root,input_att);

}
int c;

void printInOrderinQ10(struct Node *root,int *n) {
  if (root != NULL) {
  	printInOrderinQ10(root->left,&n);
    // printf("Song: %s\n", root->song_name);
	// printf("Singer: %s\n", root->singer);
    // printf("Lyricist: %s\n", root->lyricist);
    // printf("Album/Film: %s\n", root->album);
    // printf("Composer: %s\n", root->composer);
    // printf("Genre: %s\n", root->genre);
    // printf("Duration: %d seconds\n", root->duration);
    (*n)--;
    if(*n==0){
    	if(root->flag==0){
        	root->flag=1;
        	c++;
	        printf("index: %s\n", root->index);
	        printf("Song: %s\n", root->song_name);
	        printf("Singer: %s\n", root->singer);
	        printf("Lyricist: %s\n", root->lyricist);
	        printf("Album/Film: %s\n", root->album);
	        printf("Composer: %s\n", root->composer);
	        printf("Genre: %s\n", root->genre);
	        printf("Duration: %d seconds\n", root->duration);
    	}
    }

    printInOrderinQ10(root->right,&n);
  }
}


void shuffle(struct Node* root){
	
	
	countinQ10 = 0;
	
	createPlaylist(root);
	
	c=0;
	
	while(c<countinQ10){
		int random_number = rand() % countinQ10+1;
		printInOrderinQ10(lptr,&random_number);
	}
	
	
}



void createPlaylistQ8(struct Node *root,struct Node *input){
	
	struct Node passedInput = *input;
	struct Node input_att;
    strcpy(input_att.album,"#");
    strcpy(input_att.composer,"#");
    strcpy(input_att.genre,"#");
    strcpy(input_att.lyricist,"#");
    strcpy(input_att.singer,"#");
    strcpy(input_att.song_name,"#");
	int choice;
    do {
        printf("\nCreate a play-list based on the attribute\n"); //update
        printf("1. song_name\n");
        printf("2. singer\n");
        printf("3. lyricist\n");
        printf("4. album\n");
        printf("5. composer\n");
        printf("6. genre\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                strcpy(input_att.song_name,passedInput.song_name);
                break;
            case 2:
                strcpy(input_att.singer,passedInput.singer);
                break;
            case 3:
                strcpy(input_att.lyricist,passedInput.lyricist);
                break;
            case 4:
            	strcpy(input_att.album,passedInput.album);
                break;
            case 5:
                strcpy(input_att.composer,passedInput.composer);
                break;
            case 6:
                strcpy(input_att.genre,passedInput.genre);
                break;
            case 0:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice, please try again.\n");
        }
    } while (choice != 0);

    
    playlist(root,input_att);

}


void createPlaylistQ9(struct Node *root){
	
	struct Node input_att;
    strcpy(input_att.album,"#");
    strcpy(input_att.composer,"#");
    strcpy(input_att.genre,"#");
    strcpy(input_att.lyricist,"#");
    strcpy(input_att.singer,"#");
    strcpy(input_att.song_name,"#");
	int choice;
    printf("\nCreate a play-list based on the attribute\n"); //update
    printf("1. song_name\n");
    printf("2. singer\n");
    printf("3. lyricist\n");
    printf("4. album\n");
    printf("5. composer\n");
    printf("6. genre\n");
    printf("0. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    switch (choice) {
        case 1:
            printf("Enter song name: ");
            scanf("%s", input_att.song_name);
            break;
        case 2:
            printf("Enter singer name: ");
            scanf("%s", input_att.singer);
            break;
        case 3:
            printf("Enter lyricist name: ");
            scanf("%s", input_att.lyricist);
            break;
        case 4:
            printf("Enter album/film name: ");
            scanf("%s", input_att.album);
            break;
        case 5:
            printf("Enter composer name: ");
            scanf("%s", input_att.composer);
            break;
        case 6:
            printf("Enter genre: ");
            scanf("%s", input_att.genre);
            break;
        case 0:
            printf("Exiting program...\n");
            break;
        default:
            printf("Invalid choice, please try again.\n");
    }

    
    playlist(root,input_att);


}

int i;

void iindexing(struct Node *root){
    if (root != NULL) {
  	iindexing(root->left);
    root->index = i++;
    root->flag=0;
    iindexing(root->right);
  }
}


void indexing(struct Node *root){
    i=0;
    iindexing(root);
}

void printInOrder(struct Node *root,int *n) {
  if (root == NULL)return;
  else {
	 printInOrder(root->left,n);

    (*n)--;
    if(*n==0){
//        printf("index: %s\n", root->index);
        printf("Song: %s\n", root->song_name);
        printf("Singer: %s\n", root->singer);
        printf("Lyricist: %s\n", root->lyricist);
        printf("Album/Film: %s\n", root->album);
        printf("Composer: %s\n", root->composer);
        printf("Genre: %s\n", root->genre);
        printf("Duration: %d seconds\n", root->duration);
        
    }

    printInOrder(root->right,n);
  }
}


void q6(struct Node *root,int n){
	
	int t=n;

    
    printInOrder(root,&t);

    int c;
    printf("Enter prev(-1) or next(1)\n");
    scanf("%d",&c);

	n+=c;

    printInOrder(root,&n);


}




void q7(struct Node *root,int n,int k){
	int t = n;
	
    printInOrder(root,&t);
    t=n;
    if(n-k>=0){
    	t -= k;
    	printInOrder(root,&t);
	}
        
	n+=k;
    printInOrder(root,&n);
}


struct Node* searchedinq8;




void searchinq8(struct Node *root,int n) {
  if (root != NULL) {
  	searchinq8(root->left,n);
    
    if(n==root->index){
    	searchedinq8 = root;
    }
	else
    	searchinq8(root->right,n);
  }
}

void q8(struct Node *root,int n){
	if(root!=NULL){
		searchedinq8 = NULL;
		searchinq8(root,n);
		createPlaylistQ8(root,searchedinq8);
	}
}


        










//-----------------------------------------------------------------------------------------------------------------------------------

struct Node * InsertData(){


    struct Node * root = NULL;
    FILE* fp;
    char line[200];
    fp = fopen("dspd6670inputs.txt", "r");
    if (fp == NULL)  
    {
        printf("Error opening file.");
        exit(1);
    }

    while(fgets(line, sizeof(line), fp) != NULL)
    {
        struct Node *new_node = (struct Node *)malloc(sizeof(struct Node ));
        sscanf(line, "%[^;]; %[^;]; %[^;]; %[^;]; %[^;]; %[^;]; %d", new_node->song_name, new_node->singer, new_node->lyricist, new_node->album, new_node->composer, new_node->genre, &(new_node->duration));

        root = insertNode(root,new_node->song_name, new_node->singer, new_node->lyricist, new_node->album, new_node->composer, new_node->genre, (new_node->duration));
        root11 = insertNode11(root11,new_node->song_name, new_node->singer, new_node->lyricist, new_node->album, new_node->composer, new_node->genre, (new_node->duration));
        
    }

    fclose(fp);

    return root;


}
void printInOrderwithoutq6(struct Node *root) {
  if (root != NULL) {
  	printInOrderwithoutq6(root->left);
    printf("Song: %s\n", root->song_name);
	printf("Singer: %s\n", root->singer);
    printf("Lyricist: %s\n", root->lyricist);
    printf("Album/Film: %s\n", root->album);
    printf("Composer: %s\n", root->composer);
    printf("Genre: %s\n", root->genre);
    printf("Duration: %d seconds\n", root->duration);
    printf("index: %d\n", root->index);
    printInOrderwithoutq6(root->right);
  }
}

int main() {
  struct Node *root = NULL;

	root = InsertData();

  printInOrderwithout(root);

  //root = deleteNode(root, "Despacito");
  indexing(root);
  //printf("\nAfter deletion: \n");
  //printInOrderwithout(root);
  printInOrderDash(root);
  int choice;
  char a[20];
	char b[20];
	char c[20];
	char d[20];
	char e[20];
	char f[20];
	int g;
	char my[100];
    char by[100];
    int ny;
    int dir;
    int ky;
    char fi[20];
    char se[20];
    int m;
	do {
        printf("\nWelcome to Music Database\n");
        printf("1. Insert a new song\n");
        printf("2. Remove duplicates\n");
        printf("3. Print playlist\n");
        printf("4. Delete a song\n");
        printf("5. Create a new playlist\n");
        printf("6. Display current song and playlist\n");
        printf("7. Display kth song from current song in playlist\n");
        printf("8. Song by serial number:\n");
        printf("9. Filter playlist\n");
        printf("10. Shuffle songs\n");
        printf("11. Range Search\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
            	printf("enter song details to be inserted followed by spaces \n");
            	scanf("%s %s %s %s %s %s %d",a,b,c,d,e,f,&g);
                root=insertNode(root,a,b,c,d,e,f,g);
                break;
            case 2:
            	printf("duplicates are not taken in considerations in making tree \n");
                printInOrderwithout(root);
                break;
            case 3:
                printInOrderwithout(root);
                printInOrderDash(root);
                break;
            case 4:
                printf("enter song name and singer name:\n");
                scanf("%s %s",my,by);
                root=deleteArtist(root,by);
                break;
            case 5:
                createPlaylist(root);
                printInOrderwithout(lptr);
                lptr=NULL;
                break;
            case 6:
                printInOrderwithoutq6(root);
                printf("enter your number of song: \n");
                scanf("%d",&ny);
                q6(root,ny);
                break;
            case 7:
                
                printf("enter a number:\n");
                scanf("%d",&ky);
                
                printf("enter direction (up or down = +/-):\n");
                scanf("%d",&dir);
                q7(root,ky,dir);
                break;
            case 8:
            	
                printf("enter a number:\n");
                scanf("%d",&m);
                q8(root,m);
                printInOrderwithout(lptr);
                lptr=NULL;
                break;
            case 9:
                createPlaylistQ9(root);
                printInOrderwithout(lptr);
                lptr=NULL;
                break;
            case 10:
                shuffle(root);
                break;
            case 11:
            	
            	printf("enter singer 1 and singer 2\n");
            	scanf("%s",fi);
            	scanf("%s",se);
                q11(root11,fi,se);
                break;
            case 0:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice, please try again.\n");
        }
    } while (choice != 0);
  return 0;
}
