package org.elsys.cgm.demo.cgmdemo;

import android.app.AlertDialog;
import android.app.Dialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.drawable.BitmapDrawable;
import android.os.Environment;
import android.support.v7.app.ActionBarActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.SeekBar;
import android.widget.TextView;
import android.widget.Toast;

import java.io.File;
import java.io.FileInputStream;


public class ImageImprovementActivity extends ActionBarActivity implements View.OnClickListener {
    private ImageView imageView;
    private Button buttonLoad;
    private Button buttonSave;
    private Bitmap image;
    private ImageImprover imgImprover;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_image_improvement);

        this.buttonLoad = (Button) findViewById(R.id.buttonLoad);
        this.buttonSave = (Button) findViewById(R.id.buttonSave);
        this.imageView = (ImageView) findViewById(R.id.imageView);
        this.image = getImageFromIntent();
        this.imageView.setImageBitmap(image);
        this.imgImprover = new ImageImprover(image, imageView, this);

        this.buttonLoad.setOnClickListener(this);
        this.buttonSave.setOnClickListener(this);

    }

    @Override
    public void onBackPressed() {
        final Intent intent = new Intent(this, MainActivity.class);
        startActivity(intent);
        finish();
        super.onBackPressed();
    }

    private void showDialogForContrast() {
        final AlertDialog.Builder popDialog = new AlertDialog.Builder(this);
        final LayoutInflater inflater = (LayoutInflater) this.getSystemService(LAYOUT_INFLATER_SERVICE);

        final View viewLayout = inflater.inflate(R.layout.seekbar_layout,
                (ViewGroup) findViewById(R.id.layout_dialog));

        final TextView item1 = (TextView) viewLayout.findViewById(R.id.textViewProgress);


        popDialog.setView(viewLayout);

        SeekBar seek1 = (SeekBar) viewLayout.findViewById(R.id.seekBar1);
        seek1.setMax(100);
        seek1.setProgress(50);
        seek1.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser){
                //Do something here with new value
                final int contrastLevel;
                if (progress == 50) {
                    contrastLevel = 0;
                } else if (progress < 50) {
                    contrastLevel = (50 - progress)*(-1);
                } else {
                    contrastLevel = progress - 50;
                }

                item1.setText("" + contrastLevel);
            }

            public void onStartTrackingTouch(SeekBar arg0) {
                // TODO Auto-generated method stub

            }

            public void onStopTrackingTouch(SeekBar seekBar) {
                // TODO Auto-generated method stub

            }
        });

        popDialog.setPositiveButton("OK",
                new DialogInterface.OnClickListener() {
                    public void onClick(DialogInterface dialog, int which) {
                        final int value = Integer.parseInt(item1.getText().toString());

                        if (value == 0 ) {
                            return;
                        }


                        if (!imgImprover.isExecuting()) {
                            imgImprover.applyContrast(image, value);
                        }

                        dialog.dismiss();
                    }
                });


        popDialog.create();
        popDialog.show();
    }

    private void showDialogForSaving() {
        new AlertDialog.Builder(this)
                .setTitle("Are you sure you want to save this picture?")
                .setPositiveButton(android.R.string.yes, new DialogInterface.OnClickListener() {
                    public void onClick(DialogInterface dialog, int which) {
                        final FileManager fManager = new FileManager(Environment.getExternalStorageDirectory() + "/Contrastinator", getApplicationContext());
                        fManager.saveBitmapToExternalStorage(((BitmapDrawable)imageView.getDrawable()).getBitmap());
                    }
                })
                .setNegativeButton(android.R.string.no, new DialogInterface.OnClickListener() {
                    public void onClick(DialogInterface dialog, int which) {
                        // do nothing
                    }
                })
                .setIcon(android.R.drawable.ic_dialog_alert)
                .show();
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

    @Override
    public void onClick(View v) {
        switch (v.getId()) {
            case R.id.buttonLoad:
                showDialogForContrast();
                break;
            case R.id.buttonSave:
                showDialogForSaving();
                break;
        }
    }
}
