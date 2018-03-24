

``` Java
/**
	创建一个简单的窗口
	学习内容： 
			JFrame
			JFrame.getContentPane()
			JFrame.setVisble()
			JFrame.setSize()
			JFrame.setDefalutCloseOperation

			Container
			Container.add()
			Container.setBackground()

			JLable
			JLable.setHorizontalAlignment()

**/

package myTest; // package

import java.awt.*; // AWT抽象窗口工具类
import javax.swing.*; // swing，AWT的增强组件

public class MyWindow extends JFrame{ // 必须继承自JFrame类(Swing的框架类)

	public void CreateFrame(String title) { // 窗口的名称可自己定
		JFrame jf = new JFrame(title); // 实例化JFrame对象
		Container container = jf.getContentPane(); // 从JFrame获取容器
		JLabel jl = new JLabel("这是一个窗体"); // 攒见一个JLabel标签
		
		jl.setHorizontalAlignment(SwingConstants.CENTER); //使标签中的文字居中
		container.add(jl); // 将标签添加到容器中
		container.setBackground(Color.white); // 设置容器的background
		jf.setVisible(true); // 使窗体可见
		jf.setSize(400, 300); // 设置窗体大小
		
		jf.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE); // 设置窗体的默认关闭方式
	}
	public static void main(String args[]) {
		MyWindow window = new MyWindow(); // 调用CreateFrame方法获得窗体
		window.CreateFrame("first windows");
	}
}

```

``` Java
/**
	创建一个使用按键和对话框的窗口
	学习内容：
			JDialog
			JDialog.setBounds()
			JDialog.setVisible()

			JButton
			JButton.setBounds()
			JButton.addActionListener()

			ActionListener
			ActionListener.actionPerfomed()
			
**/
package myTest;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.*;

class MyDialog extends JDialog{ // JDialog 是对话框

	public MyDialog(MyFrame frame) {
		super(frame,"第一个JDialog窗体",true);
		Container container = getContentPane();
		container.add(new JLabel("这是一个对话框"));
		setBounds(120,120,100,100); // 设置Dialog窗体大小
	}
}

public class MyFrame extends JFrame{ // JFrame 窗体

	public static void main(String args[]) {
		new MyFrame(); 
	}
	
	public MyFrame() {
		// 容器
		Container container = this.getContentPane(); // 获得本窗口JFrame的容器
		container.setLayout(null); 

		// 标签
		JLabel jl=new JLabel("这是一个JFrame窗口"); // 标签文字
		jl.setHorizontalAlignment(SwingConstants.CENTER); // 标签居中
		container.add(jl); // 将标签加入容器中

		// 按钮
		JButton bl = new JButton("弹出对话框"); // 按钮
		bl.setBounds(10,10,100,21); // 设置大小
		bl.addActionListener(new ActionListener() { // 为按键添加鼠标单击事件

			public void actionPerformed(ActionEvent e) { // 处理事件的方法
				MyDialog dialog = new MyDialog(MyFrame.this); // 新建一个Dialog窗体
				dialog.setVisible(true); // 使Dialog窗体可见
			}

		});
		container.add(bl); // 将按键添加到容器中

		// 窗口本身
		this.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE); // 设置关闭方式
		this.setVisible(true); // 使Frame窗体可见
		this.setSize(300, 300); // 设置Frame窗体大小
	}
}

```

``` Java
/**
	创建图标Icon
	学习内容:
			Icon接口
			Icon.getIconWidth()
			Icon.getIconHeight()
			Icon.paintIcon()
**/

package myTest;

import java.awt.*;
import javax.swing.*;

public class DrawIcon implements Icon { // 实现Icon接口后可作为图标使用
	
	private int width; // 图片的宽
	private int height; // 图片的高
	
	public DrawIcon(int width,int height) // 构造函数
	{
		this.height=height;
		this.width=width;
	}
	

	// 重载paintIcon,必须有，用于绘制图标
	@Override
	public void paintIcon(Component c, Graphics g, int x, int y) { 
		g.fillOval(x, y, width, height);
	}

	// 重载getIconWidth，必须有，用于获得图像的宽
	@Override
	public int getIconWidth() {
		return this.width;
	}

	// 重载getIconHeight，必须有，用于获得图像的高
	@Override
	public int getIconHeight() {
		return this.height;
	}

	// main函数	
	public static void main(String[] args) {
		
		JFrame jf=new JFrame(); // 获得JFrame
		Container container= jf.getContentPane(); // 获得容器
		
		// 设置文本标签
		DrawIcon icon = new DrawIcon(15,15); // 获得图标
		JLabel text = new JLabel("test",icon,SwingConstants.CENTER); // 将图标放在文本之前
		
		text.setHorizontalAlignment(SwingConstants.CENTER);
		text.setVerticalAlignment(SwingConstants.BOTTOM);
		container.add(text);
		
		// 设置窗口
		container.setBackground(Color.green);
		jf.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
		jf.setSize(200, 200);
		jf.setVisible(true);
		
	}
	
	
}

```

``` Java
/**
	使用图片图标
	学习内容：
			URL
			
			class.getResource()
			
			ImageIcon

			JLabel.setOpaque()

**/
package myTest;

import java.awt.*;
import java.net.URL;

import javax.swing.*;

public class MyImageIcon extends JFrame{
	public MyImageIcon() {
		Container container = this.getContentPane(); // 获得容器
		
		JLabel jl= new JLabel("JFrame窗体",JLabel.CENTER); // 获得标签
		
		URL url=MyImageIcon.class.getResource("00.jpeg"); // 获得URL,图片需与class文件放一起
		Icon icon = new ImageIcon(url); // 由URL获得图片图标
		
		// 标签设置
		jl.setIcon(icon); // 将图片图标设置为标签的图标
		jl.setHorizontalAlignment(SwingConstants.CENTER); // 标签居中
		jl.setOpaque(true); // 设置标签为不透明
		container.add(jl); // 将标签加入容器中
		
		// JFrame窗体设置
		this.setSize(1000,1000); // 设置窗体大小
		this.setVisible(true); // 使窗体可见
		this.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE); // 设置窗体默认关闭模式
	}
	
	public static void main(String[] args) {
		new MyImageIcon();
	}
	
}

```

``` Java
/**
	绝对布局
	学习内容：
			JFrame.setTitle()
			JFrame.setLayout()
			JFrame.setBounds()
			
**/
package myTest;

import java.awt.*;
import javax.swing.*;

public class AbsolutePosition extends JFrame{
	public AbsolutePosition() {
		this.setTitle("绝对布局窗口"); // 设置窗口标题
		this.setLayout(null); // 使该窗口取消布局管理器设置
		this.setBounds(0,0,200,150); // 绝对定位窗口的位置和大小
		
		Container container= this.getContentPane(); // 获得容器
		JButton b = new JButton("按钮一"); // 按钮
		b.setBounds(10,30,80,30); // 设置按钮的位置和大小
		container.add(b); // 加入容器
		
		this.setVisible(true); // 使窗体可见
		this.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE); // 设置窗体关闭方式
	}
	
	public static void main(String[] args) {
		new AbsolutePosition();
	}
}

```

``` Java
/**
	流布局管理器
	学习内容：
			JFrame.setLayout()

			FlowLayout
**/
package myTest;

import java.awt.*;
import javax.swing.*;

public class FlowLayoutPosition extends JFrame{
	public FlowLayoutPosition() {
		this.setTitle("使用流布局管理器"); // 设置标题
		Container c = this.getContentPane(); // 获得容器
		this.setLayout(new FlowLayout(FlowLayout.RIGHT,10,10)); // 设置为流布局管理器，右对齐，组件间水平方向间隔为10，垂直方向间隔为10
		for(int i=0;i<10;i++){ 
			c.add(new JButton("button"+i)); // 添加按键， 按键会按照流布局管理器自动排列
		}
		this.setSize(300,200); // 设置窗口大小
		this.setVisible(true); // 使窗口可见
		this.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE); // 设置默认关闭方式
	}
	
	public static void main(String[] args) {
		new FlowLayoutPosition();
	}
}

```

``` Java
/**
	边界布局管理器
	学习内容：
			BorderLayout

			JFrame.add()
**/
package myTest;

import java.awt.*;
import javax.swing.*;

public class BorderLayoutPosition extends JFrame{

	String[] border = {BorderLayout.CENTER,BorderLayout.NORTH,BorderLayout.SOUTH,BorderLayout.WEST,BorderLayout.EAST}; // 边界布局的名称
	String[] buttonName = { "center","north","south","west","east"}; //  按键名
	
	public BorderLayoutPosition() {
		this.setTitle("使用边界布局管理器"); // 设置标题
		Container c = this.getContentPane(); // 获得容器
		this.setLayout(new BorderLayout()); // 设置边界
		for(int i=0;i<border.length;i++) { 
			c.add(border[i], new JButton(buttonName[i])); // 在指定位置添加按键
		}
		
		this.setSize(350,200); // 设置窗口大小
		this.setVisible(true); // 使窗口可见
		this.setDefaultCloseOperation(WindowConstants.DISPOSE_ON_CLOSE); // 设置窗口默认关闭模式
	}
	
	public static void main(String[] args) {
		new BorderLayoutPosition();
	}
}

```

``` Java
/**
	网格布局管理器
	学习内容：
			GridLayout
**/
package myTest;

import java.awt.*;
import javax.swing.*;

public class GridLayoutPosition extends JFrame {
	public GridLayoutPosition() {
		Container c = this.getContentPane();
		this.setLayout(new GridLayout(7,3,5,5)); // 设置为7行3列的网格，组件间间隔为5
												 // 如果组件数超过7*3，则会自动调整布局，原则是保持行数不变，改变列数
												 // 如果组件数小于等于6*3，则会自动调整布局，原则是保持行数不变，改变列数
		for(int i=0;i<20;i++) {
			c.add(new JButton("button"+i)); // 组件自动排列
		}
		this.setSize(300, 300);
		this.setTitle("使用网格布局管理器");
		this.setVisible(true);
		this.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
	}
	
	public static void main(String[] args) {
		new GridLayoutPosition();
	}
}

```

``` Java
/**
	JPanel面板
	学习内容：
			JPanel
			JPanel.add()
**/
package myTest;


import java.awt.Container;
import java.awt.GridLayout;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.WindowConstants;

public class JPanelTest extends JFrame {
	public JPanelTest() {
		Container c = getContentPane(); 
		
		c.setLayout(new GridLayout(2,1,10,10)); // 设置为网格布局管理器
		
		// JPanel面板
		JPanel p1 = new JPanel(new GridLayout(1,3,10,10));
		JPanel p2 = new JPanel(new GridLayout(1,2,10,10));
		JPanel p3 = new JPanel(new GridLayout(1,2,10,10));
		JPanel p4 = new JPanel(new GridLayout(2,1,10,10));
		
		// 向面板添加组件
		p1.add(new JButton("1"));
		p1.add(new JButton("2"));
		p1.add(new JButton("3"));
		p2.add(new JButton("4"));
		p2.add(new JButton("5"));
		p3.add(new JButton("6"));
		p3.add(new JButton("7"));
		p4.add(new JButton("8"));
		p4.add(new JButton("9"));
		
		// 将面板添加到容器中
		c.add(p1);
		c.add(p2);
		c.add(p3);
		c.add(p4);
		
		// 窗口设置
		this.setVisible(true);
		this.setSize(500, 500);
		this.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
		this.setTitle("使用JPanel面板");
	}
	
	public static void main(String[] args) {
		new JPanelTest();
	}
}

``` Java
/**
	JScrollPane面板
	学习内容：
			JTextArea

			JScrollPane
**/

package myTest;

import java.awt.*;
import javax.swing.*;
import javax.swing.JFrame;

public class JScrollPaneTest extends JFrame {
	public JScrollPaneTest() {
		Container c= getContentPane();

		JTextArea ta = new JTextArea(20,50); // 创建文本域

		JScrollPane sp = new JScrollPane(ta); // 创建带滚动条的面板，JScrollPane只能添加一个组件，如要添加多个可结合JPanel使用
		c.add(sp); // 将面板加入容器
		
		this.setSize(200,200);
		this.setVisible(true);
		this.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
	}
	
	public static void main(String[] args) {
		new JScrollPaneTest();
	}
}

```

``` Java
/**
	按钮组件
	学习内容：
			JButton.setMaximumSize()
			JButton.setHideActionText()
			JButton.setToolTipText()
			JButton.setBorderPainted()
			JButton.setEnabled()

			Dimension

			JOptionPane
			JOptionPane.showMessageDialog()
**/

package myTest;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.net.URL;

import javax.swing.*;

public class JButtonTest extends JFrame {
	public JButtonTest() {
		URL url = MyImageIcon.class.getResource("00.jpeg");
		Icon icon = new ImageIcon(url); // 加载图片作为按键的图标
		this.setLayout(new GridLayout(3,2,5,5));
		Container c=this.getContentPane();
		for(int i=0;i<5;i++) {
			JButton J=new JButton("button"+i,icon);
			c.add(J);
			if(i%2==0) {
				J.setEnabled(false); // 设置一些按钮不可用
			}
		}
		JButton jb=new JButton();
		jb.setMaximumSize(new Dimension(90,30)); // 设置按钮与图pain相同大小
		jb.setIcon(icon); 
		jb.setHideActionText(true); // 隐藏文本
		jb.setToolTipText("图片按钮"); // 设置按钮提示文字
		jb.setBorderPainted(false); // 设置按钮边界不显示
		jb.addActionListener( // 设置按钮监听事件
				new ActionListener() {
					public void actionPerformed(ActionEvent e) {
						JOptionPane.showMessageDialog(null,"弹出对话框");
					}
				}
		);
		c.add(jb);
		this.setVisible(true);
		this.setSize(300,300);
		this.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
	}
	
	public static void main(String[] args) {
		new JButtonTest();
	}
}

```

``` Java
/**
	单选框与复选框
	学习内容：
			JCheckBox
			JCheckBox.addActionListener()

			JTextArea.append()
	
			JRadioButton
			JRadioButton.addActionListener()

			ButtonGroup
			ButtonGroup.add()
**/
package myTest;

import javax.swing.JFrame;
import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class BoxTest extends JFrame {
	public BoxTest() {
		
		Container c = this.getContentPane();
		c.setLayout(new BorderLayout());
		
		JPanel panel1 = new JPanel();
		JPanel panel2 = new JPanel();
		
		// 设置用于输出的文本框
		c.add(panel1,BorderLayout.NORTH);
		JTextArea jt=new JTextArea(10,20);
		JScrollPane scrollPane = new JScrollPane(jt);
		panel1.add(scrollPane);
		
		// 设置复选框
		c.add(panel2,BorderLayout.SOUTH);
		JCheckBox[] jc = {new JCheckBox(),new JCheckBox(), new JCheckBox()}; // 复选框
		panel2.add(jc[0]); 
		jc[0].addActionListener(
				new ActionListener() {
					public void actionPerformed(ActionEvent e) {
						jt.append("复选框0被选中\n");
					}
				}
		);
		panel2.add(jc[1]);
		jc[1].addActionListener(
				new ActionListener() {
					public void actionPerformed(ActionEvent e) {
						jt.append("复选框1被选中\n");
					}
				}
		);
		panel2.add(jc[2]);
		jc[2].addActionListener(
				new ActionListener() {
					public void actionPerformed(ActionEvent e) {
						jt.append("复选框2被选中\n");
					}
				}
		);
		
		// 设置单选框
		JRadioButton[] jr= {new JRadioButton("0"),new JRadioButton("1"),new JRadioButton("2")}; // 单选框
		ButtonGroup group = new ButtonGroup(); // 按键组
		for(int i=0;i<jr.length;i++)
		{
			group.add(jr[i]);
			panel2.add(jr[i]);
		}
		jr[0].addActionListener(
				new ActionListener() {
					public void actionPerformed(ActionEvent e) {
						jt.append("单选框0被选中\n");
					}
				}
		);
		jr[1].addActionListener(
				new ActionListener() {
					public void actionPerformed(ActionEvent e) {
						jt.append("单选框1被选中\n");
					}
				}
		);
		jr[2].addActionListener(
				new ActionListener() {
					public void actionPerformed(ActionEvent e) {
						jt.append("单选框2被选中\n");
					}
				}
		);
		
		this.setVisible(true);
		this.setSize(400, 400);
		this.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
	}
	
	public static void main(String[] args) {
		new BoxTest();
	}
}

```

``` Java
/**
	下拉列表框组件
	学习内容：
			JComboBox<String>
			
			AbstractListModel<String>

			ComboBoxModel<String> ---- interface


**/
package myTest;

import javax.swing.JFrame;
import javax.swing.*;
import java.awt.*;
import java.util.Vector;

public class JComboBoxModelTest extends JFrame {
	JComboBox<String> jc1 = new JComboBox<>(new MyComboBox()); // 利用另一个类
	JComboBox<String> jc2 = new JComboBox<>(new String[]{"a","b","c"}); // 使用数组作为列表的内容

	JLabel jl = new JLabel("请输入证件:");
	
	
	public JComboBoxModelTest() {
		Container container = this.getContentPane();
		container.setLayout(new FlowLayout());
		container.add(jl);
		container.add(jc1); // 将下拉列表加入窗口
		container.add(jc2);
		
		this.setVisible(true);
		this.setSize(500,500);
		this.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
	}
	
	public static void main(String[] args)
	{
		new JComboBoxModelTest();
	}
}


class MyComboBox extends AbstractListModel<String> implements ComboBoxModel<String>{

	String selectedItem = null;
	String[] test = {"身份证","军人证","学生证","工作证"};
	
	// 为使该类可被作为列表的内容，需实现以下四个方法

	@Override
	public int getSize() { // 获得列表的总长度
		// TODO Auto-generated method stub
		return test.length;
	}

	@Override
	public String getElementAt(int index) { // 获得可查看列表内容的索引
		// TODO Auto-generated method stub
		return test[index];
	}

	@Override
	public void setSelectedItem(Object anItem) { //设置当前选择对象
		// TODO Auto-generated method stub
		selectedItem = (String)anItem;
	}

	@Override
	public Object getSelectedItem() { // 获得当前选择对象
		// TODO Auto-generated method stub
		return selectedItem;
	}
	
}
```

``` Java
/**
	列表框组件
	学习内容：
			JList<String>
			AbstractListModel

**/

package myTest;

import java.awt.*;
import javax.swing.*;

public class JListTest extends JFrame{

	String[] contents1 = {"列表1","列表2","列表3","列表4"};
	
	public JListTest(){
		JList<String> list1 = new JList<>(contents1);
		JList<String> list2 = new JList<>(new MyListModel());
		
		Container container = this.getContentPane();
		container.setLayout(new FlowLayout());
		
		container.add(list1);
		container.add(list2);
		
		this.setVisible(true);
		this.setSize(500, 500);
		this.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
		
		
		
	}
	
	public static void main(String[] args) {
		new JListTest();
	}
}

class MyListModel extends AbstractListModel<String>{

	String[] contents2 = {"列表-1","列表-2","列表-3","列表-4"};
	
	@Override
	public int getSize() {
		// TODO Auto-generated method stub
		return contents2.length;
	}

	@Override
	public String getElementAt(int index) {
		// TODO Auto-generated method stub
		return contents2[index];
	}
	
}

```

``` Java
/**
	文本框 密码框 文本域
	学习内容：
			JTextField
			JTextField.setText()
			JTextField.requestFocus()

			JPasswordField
			JPasswordField.setText()
			JPasswordField.requestFocus()

			JTextArea
			

**/
package myTest;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.*;


public class JTextFieldTest extends JFrame{

	public JTextFieldTest() {
		Container container = this.getContentPane();

		// 文本框
		JTextField textField = new JTextField("aaaa", 20); // 单行输入
		final JButton button1 = new JButton("清除");
		
		textField.addActionListener(new ActionListener() { // 设置按回车时的事件
			public void actionPerformed(ActionEvent e) {
				textField.setText("触发事件");
			}
		});
		button1.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				textField.setText(""); // 将文本框清空
				textField.requestFocus(); // 焦点回到文本框
			}
		});
		
		// 密码框
		JPasswordField passwordField = new JPasswordField("000000",20);
		final JButton button2 = new JButton("清除");
		passwordField.setEchoChar('#'); // 设置回显字符
		button2.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				passwordField.setText(""); // 清空密码框
				passwordField.requestFocus(); // 焦点回到密码框
			}
		});
		
		// 文本域
		JTextArea textArea = new JTextArea("文本域",6,20); // 多行输入
		
		container.setLayout(new FlowLayout(FlowLayout.CENTER,10,10));
		container.add(textField);
		container.add(button1);
		container.add(passwordField);
		container.add(button2);
		container.add(textArea);
		
		
		this.setVisible(true);
		this.setSize(500,500);
		this.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
	}
	
	public static void main(String[] args){
		new JTextFieldTest();
	}
}

```

``` Java
/**
	动作事件监听器 焦点事件监听器
	学习内容：
			ActionListener
			FocusListener
**/
package myTest;

import java.awt.*;
import javax.swing.*;
import java.awt.event.*;

public class EventTest extends JFrame{
	
	private JTextField textField = new JTextField(10);
	private JButton button = new JButton("清除");
	
	
	class EventListeners implements ActionListener, FocusListener{ // 实现动作事件监听器和焦点事件监听器

		@Override
		public void actionPerformed(ActionEvent e) {  // 为按键准备
			// TODO Auto-generated method stub
			textField.setText(""); // 将文本框清空
		}

		@Override
		public void focusGained(FocusEvent e) { // 为文本框准备
			// TODO Auto-generated method stub
			textField.setText("Gain focus"); // 显示获得焦点
		}

		@Override
		public void focusLost(FocusEvent e) { // 为文本框准备
			// TODO Auto-generated method stub
			textField.setText("Lose focus"); // 显示失去焦点
		}
		
	}
	
	public EventTest(){
		Container container = this.getContentPane();
		container.setLayout(new FlowLayout(FlowLayout.CENTER));
		
		this.textField.addFocusListener(new EventListeners());
		this.button.addActionListener(new EventListeners());
		
		container.add(this.textField);
		container.add(this.button);
		
		this.setVisible(true);
		this.setSize(500,500);
		this.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
		
	}
	
	public static void main(String[] args) {
		new EventTest();
	}
	
}

```

``` Java
/**
	小总结
**/

package LittleTest;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class swingTest extends JFrame{

	
	
	
	public void createWindow() {
		Container container = this.getContentPane();
		container.setLayout(null);
		
		// 标题
		JPanel panel1 = new JPanel();
		panel1.setLayout(new FlowLayout(FlowLayout.CENTER,10,10));
		JLabel title = new JLabel();
		title.setText("Swing test");
		title.setSize(20,20);
		panel1.add(title);
		panel1.setBounds(20,20,200,30);
		container.add(panel1);
		
		// 滚动文本域
		JPanel panel3 = new JPanel();
		panel3.setLayout(null);
		
		JTextArea textArea = new JTextArea("begin\n",100,100);
		JScrollPane scrollPane = new JScrollPane(textArea);
		textArea.setBounds(0,0,30,30); 
		scrollPane.setBounds(0,0,200,300);
		
		JButton button1 = new JButton("清除");
		button1.setBounds(70,310,60,30);
		button1.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) {
				// TODO Auto-generated method stub
				textArea.setText("");
			}
			
		});
		
		panel3.add(scrollPane);
		panel3.add(button1);
		panel3.setBounds(20,60,200,400);
		container.add(panel3);
		
		// 下拉列表
		JPanel panel2 = new JPanel();
		panel2.setLayout(new FlowLayout(FlowLayout.CENTER,10,10));
		String[] comboList = {"列表1","列表2","列表3","列表4"};
		JComboBox<String> comboBox = new JComboBox<>();
		for(int i=0;i<comboList.length;i++)
		{
			comboBox.addItem(comboList[i]); // 需放在块中且JComboBox由数组初始化才能使用此方法
		}
		comboBox.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) {
				// TODO Auto-generated method stub
				textArea.append("切换到"+(String)(comboBox.getSelectedItem())+'\n');
			}
		});
		panel2.add(comboBox);
		panel2.setBounds(250,20,200,40);
		container.add(panel2);		
		
		// 复选框 和 单选框
		JPanel panel4 = new JPanel();
		panel4.setLayout(new GridLayout(2,3));
		// 复选框
		JCheckBox checkBox[]= {new JCheckBox("复选框0"),new JCheckBox("复选框1"),new JCheckBox("复选框2")};
		for(int i=0;i<checkBox.length;i++) {
			panel4.add(checkBox[i]);
			checkBox[i].addActionListener(new ActionListener() {

				@Override
				public void actionPerformed(ActionEvent e) {
					// TODO Auto-generated method stub
					JCheckBox checkBoxs = (JCheckBox)e.getSource();
					if(checkBoxs.isSelected())
						textArea.append(checkBoxs.getText() + "被选中\n");	
					else
						textArea.append(checkBoxs.getText() +"被取消选中\n");
				}
				
			});
		}
		// 单选框
		JRadioButton radioButton[] = {new JRadioButton("单选框0"),new JRadioButton("单选框1"),new JRadioButton("单选框2")};
		ButtonGroup group = new ButtonGroup();
		for(int i=0;i<radioButton.length;i++) {
			group.add(radioButton[i]);
			panel4.add(radioButton[i]);
			radioButton[i].addActionListener(new ActionListener() {

				@Override
				public void actionPerformed(ActionEvent e) {
					// TODO Auto-generated method stub
					JRadioButton radioButton = (JRadioButton)e.getSource();
					textArea.append("当前选中了"+(String)radioButton.getText()+'\n');
				}
				
			});
		}
		
		panel4.setBounds(250,60,250,200);
		container.add(panel4);
		
		// 文本框 和 密码框
		JPanel panel5 = new JPanel();
		panel5.setLayout(new FlowLayout(FlowLayout.CENTER,20,10));
		panel5.setBounds(250,270,250,200);
		container.add(panel5);
		// 文本框
		JTextField textField = new JTextField("default",20);
		panel5.add(textField);
		textField.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) {
				// TODO Auto-generated method stub
				textArea.append("文本框中输入了 "+ textField.getText() +'\n');
			}
			
		});
		// 密码框
		JPasswordField passwordField = new JPasswordField(20);
		passwordField.setEchoChar('#');
		passwordField.setSize(50,25);
		panel5.add(passwordField);
		passwordField.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) {
				// TODO Auto-generated method stub
				textArea.append("输入的密码被储存为："+passwordField.getPassword()+"\n");
			}
			
		});
		
		this.setVisible(true);
		this.setTitle("swing test");
		this.setSize(600,500);
		this.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
		
	}
	
	
	public static void main(String[] args) {
		swingTest test = new swingTest();
		test.createWindow();
	}
	
}


```
