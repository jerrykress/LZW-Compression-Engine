repeat(){
	for i in {1..100}; do echo -n "$1"; done
}

# FILES=$(repeat 'test_input/book.txt.z test_input/hello.txt.z test_input/poem.txt.z test_input/icon.png.z ')

FILES='test_input/book.txt.lz test_input/hello.txt.lz test_input/poem.txt.lz test_input/icon.png.lz'

cp build/LZW_Decompressor ./LZW_Decompressor

./LZW_Decompressor $FILES

rm ./LZW_Decompressor