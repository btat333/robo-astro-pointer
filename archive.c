
	// Boot up the FSW tasks
	if ((error_num = pthread_create(&gps_reciever_listener, NULL, create_gps_listener, zmq_ctx)))
	{
		fprintf (stderr, "Unable to start gps: %s\n", strerror (errno)) ;
		release_app_memory();
		return 1 ;
	}
	if ((error_num = pthread_create(&magnetometer_listener, NULL, create_magnetometer_listener, zmq_ctx)))
	{
		fprintf (stderr, "Unable to start magnetometer: %s\n", strerror (errno)) ;
		release_app_memory();
		return 1 ;
	}