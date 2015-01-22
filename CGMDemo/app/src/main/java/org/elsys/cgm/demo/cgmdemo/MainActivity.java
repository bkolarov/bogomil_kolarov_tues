package org.elsys.cgm.demo.cgmdemo;

import android.content.ContentResolver;
import android.content.Context;
import android.content.Intent;
import android.database.Cursor;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.net.Uri;
import android.os.Environment;
import android.provider.MediaStore;
import android.support.v7.app.ActionBarActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;

public class MainActivity extends ActionBarActivity implements View.OnClickListener {
    private static final int CAMERA_REQ_CODE = 1888;
    private static final int GALLERY_REQ_CODE = 1777;

    private final String TAG = "MainActivity";

    private Button buttonShoot;
    private Button buttonOpenGallery;
    private Uri imageUri;

    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        Bitmap image = null;


        Log.i(TAG, "onActivityResult called");

        switch (requestCode) {
            case CAMERA_REQ_CODE:
                if (resultCode == RESULT_OK) {
                    //image = (Bitmap) data.getExtras().get("data");
                    Log.i(TAG, imageUri.toString());
                    this.getContentResolver().notifyChange(imageUri, null);
                    final ContentResolver contentResolver = this.getContentResolver();

                    try {
                        image = MediaStore.Images.Media.getBitmap(contentResolver, imageUri);

                        if (image == null) {
                            Log.i(TAG, "image is null");
                        }

                    } catch (Exception e) {
                        e.printStackTrace();
                    }
                }
                break;
            case GALLERY_REQ_CODE:
                if (resultCode == RESULT_OK) {
                    Uri selectedImage = data.getData();
                    String[] filePathColumn = {MediaStore.Images.Media.DATA};

                    Cursor cursor = getContentResolver().query(
                            selectedImage, filePathColumn, null, null, null);
                    cursor.moveToFirst();

                    int columnIndex = cursor.getColumnIndex(filePathColumn[0]);
                    String filePath = cursor.getString(columnIndex);
                    cursor.close();

                    image = BitmapFactory.decodeFile(filePath);
                }
                break;
        }

        final Intent improveImageIntent = new Intent(this, ImageImprovementActivity.class);

        try {
            improveImageIntent.putExtra("image", packBitmap(image));
        } catch (IOException | NullPointerException e) {
            e.printStackTrace();
            return;
        } finally {
            startActivity(improveImageIntent);
            finish();
        }



    }

    private String packBitmap(Bitmap bmp) throws IOException, NullPointerException {
        Log.i(TAG, "packing bitmap");
        String filename = "bitmap.png";
        FileOutputStream stream = this.openFileOutput(filename, Context.MODE_PRIVATE);
        bmp.compress(Bitmap.CompressFormat.PNG, 100, stream);

        //Cleanup
        stream.close();
        bmp.recycle();

        Log.i(TAG, "packing bitmap - done");

        return filename;
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        this.buttonShoot = (Button) findViewById(R.id.buttonShoot);
        this.buttonOpenGallery = (Button) findViewById(R.id.buttonOpenGallery);

        this.buttonShoot.setOnClickListener(this);
        this.buttonOpenGallery.setOnClickListener(this);
    }

    private void openCamera() {
        final Intent cameraIntent = new Intent(MediaStore.ACTION_IMAGE_CAPTURE);

        final File photoFile;
        try {
            photoFile = createTemporaryFile("contrastinator_temp_image", ".png");
            photoFile.delete();
        } catch (IOException e) {
            e.printStackTrace();
            return;
        }

        imageUri = Uri.fromFile(photoFile);
        cameraIntent.putExtra(MediaStore.EXTRA_OUTPUT, imageUri);

        startActivityForResult(cameraIntent, CAMERA_REQ_CODE);
    }

    private File createTemporaryFile(String name, String extension) throws IOException {
        final File temp = new File(Environment.getExternalStorageDirectory().getAbsolutePath() + "/.temp/");
        if (!temp.exists()) {
            temp.mkdirs();
        }
        return File.createTempFile(name, extension, temp);
    }

    private void openGallery() {
        final Intent galleryIntent = new Intent(Intent.ACTION_PICK, android.provider.MediaStore.Images.Media.EXTERNAL_CONTENT_URI);
        startActivityForResult(galleryIntent, GALLERY_REQ_CODE);
    }

    @Override
    public void onClick(View v) {
        switch(v.getId()) {
            case R.id.buttonShoot:
                openCamera();
                break;
            case R.id.buttonOpenGallery:
                openGallery();
                break;
            default:
                return;
        }
    }
}
