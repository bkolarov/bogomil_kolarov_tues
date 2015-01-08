package org.elsys.cgm.demo.cgmdemo;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.Color;
import android.os.AsyncTask;
import android.util.Log;
import android.widget.ImageView;
import android.widget.Toast;

/**
 * Created by crash-id on 08.01.15.
 */
public class ImageImprover {
    private Bitmap image;
    private Bitmap improvedImage;
    private ImageView imgView;
    private Context context;

    private boolean isExecuting = false;

    public ImageImprover(Bitmap image) {
        this.image = image;

    }

    public ImageImprover(Bitmap image, ImageView imgView, Context context) {
        this.image = image;
        this.imgView = imgView;
        this.context = context;
    }

    public boolean isExecuting() {
        return isExecuting;
    }

    public void applyContrast(Bitmap image, double contrastVal) {
        new Calculation(contrastVal).execute();
    }

    private int calculateContrastForColor(int color, double contrast) {
        int resultColor = (int)(((((color / 255.0) - 0.5) * contrast) + 0.5) * 255.0);
        resultColor = truncate(resultColor);

        return resultColor;
    }

    private int truncate(int value) {
        if (value < 0) {
            return 0;
        } else if (value > 255) {
            return 255;
        }

        return value;
    }

    private class Calculation extends AsyncTask<Void, Void, Bitmap> {
        private double contrastVal;
        private Bitmap improvedImage;

        @Override
        protected void onPreExecute() {
            isExecuting = true;
            super.onPreExecute();
        }

        public Calculation(double contrastVal) {
            this.contrastVal = contrastVal;
        }

        @Override
        protected void onPostExecute(Bitmap resultImage) {
            isExecuting = false;
            imgView.setImageBitmap(resultImage);
            Toast.makeText(context, "Better it is.", Toast.LENGTH_SHORT).show();
            super.onPostExecute(resultImage);
        }

        @Override
        protected Bitmap doInBackground(Void... params) {
            this.improvedImage = Bitmap.createBitmap(image.getWidth(), image.getHeight(), image.getConfig());
            final int width = image.getWidth();
            final int height = image.getHeight();
            int A, R, G, B;
            int pixel;
            double contrast = Math.pow((100 + contrastVal) / 100, 2);

            for (int x = 0; x < width; x++) {
                for (int y = 0; y < height; y++) {
                    pixel = image.getPixel(x, y);
                    A = Color.alpha(pixel);

                    R = calculateContrastForColor(Color.red(pixel), contrast);
                    G = calculateContrastForColor(Color.green(pixel), contrast);
                    B = calculateContrastForColor(Color.blue(pixel), contrast);

                    improvedImage.setPixel(x, y, Color.argb(A, R, G, B));
                }
            }

            if(improvedImage == null) {
                Log.e("ImageImprover", "improvedImage IS NULL");
            }

            return improvedImage;
        }

        private int calculateContrastForColor(int color, double contrast) {
            int resultColor = (int)(((((color / 255.0) - 0.5) * contrast) + 0.5) * 255.0);
            resultColor = truncate(resultColor);

            return resultColor;
        }

        private int truncate(int value) {
            if (value < 0) {
                return 0;
            } else if (value > 255) {
                return 255;
            }

            return value;
        }
    }
}
