all:
	make -C server/
	cp server/build/bin/r-type_server .
	make -C SFML/
	cp SFML/build/bin/r-type_client .

server:
	make -C server/
	cp server/build/bin/r-type_server .

client:
	make -C SFML/
	cp SFML/build/bin/r-type_client .

clean:
	make clean -C server/
	make clean -C SFML/

fclean: clean
	make fclean -C server/
	$(RM) r-type_server
	make fclean -C SFML/
	$(RM) r-type_client

re: fclean all

.PHONY: all clean fclean re
