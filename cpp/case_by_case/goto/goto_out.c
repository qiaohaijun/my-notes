if (init1()) {
	printf("init1 failed\n");
	goto out_init1;
}

if (init2()) {
	printf("init2 failed\n");
	goto out_init2;
}

if (init3()) {
	printf("init3 failed\n");
	goto out_init3;
}

if (init4()) {
	printf("init4 failed\n");
	goto out_init4;
}

if (init5()) {
	printf("init5 failed\n");
	goto out_init5;
}

return 0;

out_init5:
	destroy4();
out_init4:
	destroy3();
out_init3:
	destroy2();
out_init2:
	destroy1();
out_init1:
	return -1;
