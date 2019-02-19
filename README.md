crazyflie_ros
=============

The following repo is based out of [whoenig/crazyflie_ros](https://github.com/whoenig/crazyflie_ros) version.

It has been flattened (remove submodules) and cleaned for custom usage. (removed unused packages as we are only using the roadrunner.)

Also, many features have been removed as it is running on an embedded computer.

## Installation

Clone the package into your catkin workspace:
```
cd Workspace/src
git clone https://github.com/umdlife/crazyflie_ros
cd Workspace
catkin build
```

## Citing This Work

If you use this work, you should still give credits to the original author by adding the following into your bibTex.

This project is published under the very permissive MIT License. However,
if you use the package we appreciate if you credit this project accordingly.

For academic publications, you can cite the following book chapter:

```latex
@Inbook{crazyflieROS,
  author={Wolfgang H{\"o}nig
          and Nora Ayanian},
  editor={Anis Koubaa},
  title={Flying Multiple UAVs Using ROS},
  bookTitle={Robot Operating System (ROS): The Complete Reference  (Volume 2)},
  year={2017},
  publisher={Springer International Publishing},
  pages={83--118},
  isbn={978-3-319-54927-9},
  doi={10.1007/978-3-319-54927-9_3},
  url={https://doi.org/10.1007/978-3-319-54927-9_3}
}

```

If your work is related to Mixed Reality, you might cite the paper which introduced the package instead, using the following bibtex entry:

```latex
@conference{HoenigMixedReality2015,
  author = {Wolfgang H{\"o}nig and Christina Milanes and Lisa Scaria and Thai Phan and Mark Bolas and Nora Ayanian},
  booktitle = {IEEE/RSJ Intl Conf. Intelligent Robots and Systems},
  pages = {5382 - 5387},
  title = {Mixed Reality for Robotics},
  year = {2015}}
```

For any other mentioning please include my affiliation (ACTLab at University of Southern California or USC in short; The link to our webpage is http://act.usc.edu) as this work was partially done as part of my research at USC.
