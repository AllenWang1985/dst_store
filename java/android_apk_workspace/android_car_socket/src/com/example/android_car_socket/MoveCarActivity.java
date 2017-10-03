package com.example.android_car_socket;

import java.io.IOException;

import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.widget.SeekBar;
import android.widget.SeekBar.OnSeekBarChangeListener;
import android.widget.TextView;
import android.widget.Toast;

public class MoveCarActivity extends Activity {

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);

		setContentView(R.layout.move_car);// ���ò�����r_and_l.xmlҳ��

		// �ѵ�ǰ����ࣨthis����ӽ��б�
		MyArrayList.list.add(this);

		// ����PWMSeekBar����
		final SeekBar PWMSeekBar = (SeekBar) findViewById(R.id.PWMSeekBar);
		final TextView PWMTextView = (TextView) findViewById(R.id.PWMTextView);

		PWMSeekBar.setOnSeekBarChangeListener(new OnSeekBarChangeListener() {

			@Override
			public void onStopTrackingTouch(SeekBar seekBar) {
				// TODO Auto-generated method stub
				// ֹͣ����seekbar
				int val = PWMSeekBar.getProgress();
				PWMTextView.setText("PWM:" + val);
			}

			@Override
			public void onStartTrackingTouch(SeekBar seekBar) {
				// TODO Auto-generated method stub
				// ��ʼ����seekbar
				int val = PWMSeekBar.getProgress();
				PWMTextView.setText("PWM:" + val);
			}

			@Override
			public void onProgressChanged(SeekBar seekBar, int progress,
					boolean fromUser) {
				// TODO Auto-generated method stub
				// seekbar��ֵ�����ı�
				int val = PWMSeekBar.getProgress();
				PWMTextView.setText("PWM:" + val);
				// str�������������
				String str = "Upw" + (val / 100 % 10) + (val / 10 % 10)
						+ (val % 10);
				// ��str�ڵ��ַ���ת��Ϊbyte����
				byte[] buffer = str.getBytes();
				// ���������out��������������
				try {
					MyArrayList.out.write(buffer, 0, buffer.length);
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
		});

	}

	public void moveButton(View v) throws IOException {
		// �����ַ����ͻ�����
		String str;
		byte[] buffer;

		switch (v.getId()) {
		case R.id.upButton:// ǰ��
			// str�������������
			str = "Umww";
			// ��str�ڵ��ַ���ת��Ϊbyte����
			buffer = str.getBytes();
			// ���������out��������������
			MyArrayList.out.write(buffer, 0, buffer.length);
			// ��˾��ӡ����ʾ�û����ͳɹ�
			Toast.makeText(MoveCarActivity.this, "ǰ���źŷ��ͳɹ�", Toast.LENGTH_SHORT)
					.show();
			break;
		case R.id.stopButton:// ֹͣ
			// str�������������
			str = "Umws";
			// ��str�ڵ��ַ���ת��Ϊbyte����
			buffer = str.getBytes();
			// ���������out��������������
			MyArrayList.out.write(buffer, 0, buffer.length);
			// ��˾��ӡ����ʾ�û����ͳɹ�
			Toast.makeText(MoveCarActivity.this, "ֹͣ�źŷ��ͳɹ�", Toast.LENGTH_SHORT)
					.show();
			break;
		case R.id.leftButton:// ��ת
			// str�������������
			str = "Umwa";
			// ��str�ڵ��ַ���ת��Ϊbyte����
			buffer = str.getBytes();
			// ���������out��������������
			MyArrayList.out.write(buffer, 0, buffer.length);
			// ��˾��ӡ����ʾ�û����ͳɹ�
			Toast.makeText(MoveCarActivity.this, "��ת�źŷ��ͳɹ�", Toast.LENGTH_SHORT)
					.show();
			break;
		case R.id.rightButton:// ��ת
			// str�������������
			str = "Umwd";
			// ��str�ڵ��ַ���ת��Ϊbyte����
			buffer = str.getBytes();
			// ���������out��������������
			MyArrayList.out.write(buffer, 0, buffer.length);
			// ��˾��ӡ����ʾ�û����ͳɹ�
			Toast.makeText(MoveCarActivity.this, "��ת�źŷ��ͳɹ�", Toast.LENGTH_SHORT)
					.show();
			break;
		case R.id.endButton:// �˳�����
			// ����MyArrayList.list�б�ر�ҳ��
			for (Activity activity : MyArrayList.list) {
				activity.finish();
			}
		default:
			break;
		}
	}

	@Override
	protected void onDestroy() {
		// TODO Auto-generated method stub
		super.onDestroy();

		// ���ûҳ����б���ɾ��
		MyArrayList.list.remove(MyArrayList.list.size() - 1);
	}
}
