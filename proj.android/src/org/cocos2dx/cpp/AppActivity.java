/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2014 Chukong Technologies Inc.
 
http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
 ****************************************************************************/
package org.cocos2dx.cpp;

import org.cocos2dx.lib.Cocos2dxActivity;

import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.view.ViewGroup;
import android.widget.RelativeLayout;

import com.adsmogo.adapters.AdsMogoCustomEventPlatformEnum;
import com.adsmogo.adview.AdsMogoLayout;
import com.adsmogo.controller.listener.AdsMogoListener;
import com.adsmogo.splash.AdsMogoSplash;
import com.adsmogo.splash.AdsMogoSplashListener;
import com.adsmogo.util.AdsMogoSplashMode;
import com.adsmogo.util.AdsMogoUtil;
import com.adsmogo.util.L;
import com.adsmogo.*;
import com.umeng.mobclickcpp.MobClickCppHelper;

public class AppActivity extends Cocos2dxActivity implements AdsMogoListener {
	private static Handler handler;
	private AdsMogoLayout adView;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		
		MobClickCppHelper.init(this);
		
		
		final RelativeLayout bannerLayout = new RelativeLayout(this);
		RelativeLayout.LayoutParams parentLayputParams = new RelativeLayout.LayoutParams(
				RelativeLayout.LayoutParams.FILL_PARENT,
				RelativeLayout.LayoutParams.FILL_PARENT);
		this.addContentView(bannerLayout, parentLayputParams);

		handler = new Handler() {
			public void handleMessage(Message msg) {

				switch (msg.what) {
				case 0:
					if (bannerLayout.getChildCount() == 0) {
						AdsMogoLayout adView = new AdsMogoLayout(AppActivity.this,"25317c5a50eb4355a490d6f30d6e62a4", false);
						RelativeLayout.LayoutParams layoutParams = new RelativeLayout.LayoutParams(
								RelativeLayout.LayoutParams.FILL_PARENT,
								RelativeLayout.LayoutParams.WRAP_CONTENT);
//						layoutParams.addRule(
//								RelativeLayout.ALIGN_PARENT_BOTTOM,
//								RelativeLayout.TRUE);
						layoutParams.addRule(
								RelativeLayout.ALIGN_PARENT_BOTTOM,
								RelativeLayout.CENTER_VERTICAL);
						bannerLayout.addView(adView, layoutParams);
					}
					break;
				case 1:
					bannerLayout.removeAllViews();
					break;
				}
			}
		};
	}

	public static void showBannerStatic() {
		Message msg = handler.obtainMessage();
		msg.what = 0;
		handler.sendMessage(msg);
	}

	public static void hideBannerStatic() {
		Message msg = handler.obtainMessage();
		msg.what = 1;
		handler.sendMessage(msg);
	}

	@Override
	public Class getCustomEvemtPlatformAdapterClass(
			AdsMogoCustomEventPlatformEnum arg0) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public void onClickAd(String arg0) {
		// TODO Auto-generated method stub

	}

	@Override
	public boolean onCloseAd() {
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	public void onCloseMogoDialog() {
		// TODO Auto-generated method stub

	}

	@Override
	public void onFailedReceiveAd() {
		// TODO Auto-generated method stub

	}

	@Override
	public void onInitFinish() {
		// TODO Auto-generated method stub

	}

	@Override
	public void onRealClickAd() {
		// TODO Auto-generated method stub

	}

	@Override
	public void onReceiveAd(ViewGroup arg0, String arg1) {
		// TODO Auto-generated method stub

	}

	@Override
	public void onRequestAd(String arg0) {
		// TODO Auto-generated method stub

	}
	
	static {
        MobClickCppHelper.loadLibrary();
	}
	
}
