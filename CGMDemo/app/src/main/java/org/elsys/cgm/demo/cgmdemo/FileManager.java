package org.elsys.cgm.demo.cgmdemo;

import android.content.Context;
import android.graphics.Bitmap;
import android.os.AsyncTask;
import android.widget.Toast;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.text.SimpleDateFormat;
import java.util.Calendar;

/**
 * Created by crash-id on 08.01.15.
 */
public class FileManager {
    private String path;
    private Context context;

    public FileManager() {

    }

    public FileManager(String path, Context context) {
        this.path = path;
        this.context = context;
    }

    public void saveBitmapToExternalStorage(Bitmap bmp) {
        new BitmapSaver(bmp).execute();

    }

    private class BitmapSaver extends AsyncTask<Void, Void, Void> {
        private Bitmap bitmap;

        public BitmapSaver(Bitmap bitmap) {
            this.bitmap = bitmap;
        }

        @Override
        protected void onPostExecute(Void aVoid) {
            Toast.makeText(context, "Image Saved", Toast.LENGTH_SHORT).show();
            super.onPostExecute(aVoid);
        }

        @Override
        protected Void doInBackground(Void... params) {
            final File f = new File(path);
            if (!f.exists()) {
                f.mkdir();
            }

            FileOutputStream out = null;
            try {
                out = new FileOutputStream(path + "/" + getCurrentDate() + ".png");
                bitmap.compress(Bitmap.CompressFormat.PNG, 100, out);
            } catch (Exception e) {
                e.printStackTrace();
            } finally {
                try {
                    if (out != null) {
                        out.close();
                    }
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }

            return null;
        }

        private String getCurrentDate() {
            final Calendar c = Calendar.getInstance();

            final SimpleDateFormat df = new SimpleDateFormat("dd-MMM-yyyy");
            final String formattedDate = df.format(c.getTime());
            return formattedDate + "-" + System.currentTimeMillis() % 1000;
        }
    }
}
