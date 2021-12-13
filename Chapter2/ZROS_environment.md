# ZROS 环境配置
## 1. 安装第三方库
- 安装wayland和weston
    ```Bash
    sudo apt-get install xwayland weston wayland-protocols libgles2-mesa-dev mesa-utils-extra libglfw3-dev
    ```
- 安装gstreamer
  ```Bash
  sudo apt-get install gstreamer1.0-alsa gstreamer1.0-plugins-base gstreamer1.0-clutter gstreamer1.0-plugins-base-apps gstreamer1.0-clutter-3.0 gstreamer1.0-plugins-base-dbg gstreamer1.0-crystalhd gstreamer1.0-plugins-base-doc gstreamer1.0-doc gstreamer1.0-plugins-good gstreamer1.0-dvswitch gstreamer1.0-plugins-good-dbg gstreamer1.0-espeak gstreamer1.0-plugins-good-doc gstreamer1.0-fluendo-mp3 gstreamer1.0-plugins-ugly gstreamer1.0-plugins-ugly-amr gstreamer1.0-libav gstreamer1.0-plugins-ugly-dbg gstreamer1.0-libav-dbg gstreamer1.0-plugins-ugly-doc gstreamer1.0-nice gstreamer1.0-pocketsphinx gstreamer1.0-packagekit gstreamer1.0-pulseaudio gstreamer1.0-plugins-bad gstreamer1.0-tools gstreamer1.0-plugins-bad-dbg gstreamer1.0-vaapi gstreamer1.0-plugins-bad-doc gstreamer1.0-vaapi-doc gstreamer1.0-plugins-bad-faad gstreamer1.0-x gstreamer1.0-plugins-bad-videoparsers libgstreamer1.0-* libgstreamermm-1.0-* libgstreamer-plugins-*
  ```
  如果是在虚拟机下安装，安装好gstreamer后，需要删除硬件加速版的libva库，否则不能视频playback
    ```Bash
    sudo dpkg -r gstreamer1.0-vaapi:amd64
    sudo dpkg -r libva-wayland1:amd64
    ```
- 安装protoc
    ```Bash
    sudo apt install protobuf-compiler
    ```
- 安装ros
  - Setup your sources.list
    ```Bash
    sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list'
    ```
  - Set up your keys
    ```Bash
    sudo apt install curl # if you haven't already installed curl

    curl -s https://raw.githubusercontent.com/ros/rosdistro/master/ros.asc | sudo apt-key add -
    ```
  - Installation
    ```Bash
    sudo apt-get update
    ```
    这一步有可能会报 (NO_PUBKEY) 的 error

    看报的错里面是哪些key没有加进去，一般都在NO_PUBKEY 后面打印出来的
    再用下面这个命令一个个加进去就是：
    ```Bash
    sudo apt-key adv --keyserver keyserver.ubuntu.com --recv-keys [key]
    ```
    安装ros kinetic的full版本
    ```Bash
    sudo apt-get install ros-kinetic-desktop-full
    ```
  - Envionment Setup
        ```Bash
        echo "source /opt/ros/kinetic/setup.bash" >> ~/.bashrc
        source ~/.bashrc
        ``` 
  - Dependencies for building packages
    ```Bash
    sudo apt install python-rosdep python-rosinstall python-rosinstall-generator python-wstool build-essential
    sudo apt install python-rosdep
    sudo rosdep init
    rosdep update
    ```
    rosdep update 卡住或者失败了没关系
- 安装opencv
  ```Bash
  sudo apt-get install libopencv-dev
  ```
- 安装其它依赖包
  ```Bash
  sudo apt-get install libnlopt-dev
  ```
------
## 2. pull代码
zros平台的代码已经提交至`zm_hwp_framework`仓库
```Bash
git clone ssh://fan.huang@shaitgrt01:29418/radar/zm_hwp_framework
```
请修改上面各自用户名对应的ssh地址后clone代码

------
## 3. 编译和运行
在代码根目录下用下面的脚本编译代码, x86平台
```Bash
./mx86
```
编译完成后，根目录下会多出一个`out`文件夹，编译出来的libs, data, 可执行程序都在这里面

运行zros需要本地有一份录制好的回放视频文件，可以去I盘上找或者找同事要，然后修改如下几个配置文件:
1. out目录下的 /out/B_DropnGo_stable/ubuntu1604_x86_64/res/camera/video_source/video_source.xml
   
   将下面的配置项改成 `video_mgr`
   ```
   <linux>
		<video_mgr>video_mgr</video_mgr>
   </linux>
    ```
2. out目录下的 out/B_DropnGo_stable/ubuntu1604_x86_64/res/playback/gstreamer_library.xml

    将path配置项改成本地视频回放文件的路劲
    ```
    <path>/home/pyli/work/video_lib/odyssey_ov10626_sy4039_201605/general/capture_68</path>
    ```
3. 将out目录下的lib路径加入到 LD_LIBRARY_PATH 里面去
    ```Bash
    export LD_LIBRARY_PATH=<lib path>:$LD_LIBRARY_PATH
    ```
4. 一般zros的launcher程序会默认加载res/launcher/下面的launcher_common.xml和 launcher_all.xml里面配置的所有节点，可以手动修改这两个配置文件中的节点启动与否，避免启动太多节点导致调试困难

配置好了后在out/.../bin目录下跑./launcher即可 