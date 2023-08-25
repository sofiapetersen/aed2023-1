void postorderTraversal( Node* node, int** result, int* index ) {
    if ( node == NULL )
        return;

    for ( int i = 0; i < node->numChildren; i++ ) {
        postorderTraversal( node->children[i], result, index );
    }
    
    *result = ( int* )realloc( *result, ( *index + 1 ) * sizeof( int ) );
    ( *result )[( *index )++] = node->val;
}

int* postorder( Node* root, int* returnSize ) {
    int* result = NULL;
    int index = 0;

    postorderTraversal( root, &result, &index );

    *returnSize = index;
    return result;
}
