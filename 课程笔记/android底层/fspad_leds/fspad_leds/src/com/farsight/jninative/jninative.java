package com.farsight.jninative;





public  class  jninative {
	
	
	static {
		
		System.loadLibrary("jninative");
		
		
	}
	public  static  native int  hello_open();
	public  static  native  int  hello_ioctl(int which,int status);
	
	
	
	
	
}