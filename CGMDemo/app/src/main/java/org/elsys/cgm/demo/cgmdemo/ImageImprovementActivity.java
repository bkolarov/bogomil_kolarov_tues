package org.elsys.cgm.demo.cgmdemo;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.drawable.BitmapDrawable;
import android.os.Environment;
import android.support.v7.app.ActionBarActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.Toast;

import java.io.File;
import java.io.FileInputStream;


public class ImageImprovementActivity extends ActionBarActivity {
    private ImageView imageView;
    private Button buttonLoad;
    private Bitmap image;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_image_improvement);

        this.buttonLoad = (Button) findViewById(R.id.buttonLoad);
        this.imageView = (ImageView) findViewById(R.id.imageView);

        this.image = getImageFromIntent();
        this.imageView.setImageBitmap(image);

        //this.image = (Bitmap) getIntent().getParcelableArrayExtra("image");

/*
        try {
            imageView.setImageBitmap(getImage());
        } catch (NullPointerException e) {
            Toast.makeText(this, "Image Null", Toast.LENGTH_SHORT).show();
        }

        buttonLoad.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                final Bitmap bmp = ((BitmapDrawable)imageView.getDrawable()).getBitmap();
                final ImageImprover imgImprover = new ImageImprover(bmp, imageView);
                imgImprover.applyContrast(bmp, 50);
            }
        });
*/
    }

    private Bitmap getImageFromIntent() {
        Bitmap bmp = null;
        String filename = getIntent().getStringExtra("image");
        try {
            FileInputStream is = this.openFileInput(filename);
            bmp = BitmapFactory.decodeStream(is);
            is.close();
        } catch (Exception e) {
            e.printStackTrace();
        }

        return bmp;
    }

    private Bitmap getImage() {
        final File imgFile = new File(Environment.getExternalStorageDirectory() + "/testImage2.jpg" );

        if (imgFile.exists()) {
            Bitmap bmp = BitmapFactory.decodeFile(imgFile.getAbsolutePath());
            return bmp;
        }

        return null;
    }
}
