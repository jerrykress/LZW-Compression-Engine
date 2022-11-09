repeat(){
	for i in {1..100}; do echo -n "$1"; done
}

X_TEST_FILES_100=$(repeat 'book.txt.z hello.txt.z poem.txt.z icon.png.z ')

X_TEST_FILES='book.txt.z hello.txt.z poem.txt.z icon.png.z '

C_TEST_FILES_100=$(repeat 'book.txt hello.txt poem.txt icon.png ')

C_TEST_FILES='book.txt hello.txt poem.txt icon.png'

cp ../build/Compressor ./Compressor

./Compressor -c $C_TEST_FILES
./Compressor -x $X_TEST_FILES

rm ./Compressor