package com.farsight.fspad_leds;


import android.app.Activity;
import android.os.Bundle;
import android.view.Menu;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;

import com.farsight.jninative.jninative;

public class MainActivity extends Activity {

	
	private  Button  button  = null;
	private  boolean  ledon   =  false;
	
	//jninative  jninative   = new  jninative();
	 
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        button  = (Button) findViewById(R.id.button);
       
       
        button.setOnClickListener(new  OnClickListener() {
			
			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub 
				ledon  = !ledon;
				// jninative.hello_open();
				if(ledon)
				{
					
					button.setText("ledoff");
					//jninative.hello_ioctl(1, 1);
					
				}
				else{
					
					
					button.setText("ledon");
				//	jninative.hello_ioctl(1, 0);
					
				}
				
			}
		});
    }


    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.main, menu);
        return true;
    }
    
}
