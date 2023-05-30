import numpy as np
import matplotlib.pyplot as plt
from skimage import io
import open3d as o3d
from PIL import Image


# ==============================================================================
#                                                                   SCALE_TO_255
# ==============================================================================
def scale_to_255(a, min, max, dtype=np.uint8):
    """ Scales an array of values from specified min, max range to 0-255
        Optionally specify the data type of the output (default is uint8)
    """
    return (((a - min) / float(max - min)) * 255).astype(dtype)


# ==============================================================================
#                                                         POINT_CLOUD_2_BIRDSEYE
# ==============================================================================
def point_cloud_2_birdseye(points,
                           res=0.1,
                           side_range=(-10., 10.),  # left-most to right-most
                           fwd_range = (-10., 10.), # back-most to forward-most
                           height_range=(-2., 2.),  # bottom-most to upper-most
                           ):
    """ Creates an 2D birds eye view representation of the point cloud data.

    Args:
        points:     (numpy array)
                    N rows of points data
                    Each point should be specified by at least 3 elements x,y,z
        res:        (float)
                    Desired resolution in metres to use. Each output pixel will
                    represent an square region res x res in size.
        side_range: (tuple of two floats)
                    (-left, right) in metres
                    left and right limits of rectangle to look at.
        fwd_range:  (tuple of two floats)
                    (-behind, front) in metres
                    back and front limits of rectangle to look at.
        height_range: (tuple of two floats)
                    (min, max) heights (in metres) relative to the origin.
                    All height values will be clipped to this min and max value,
                    such that anything below min will be truncated to min, and
                    the same for values above max.
    Returns:
        2D numpy array representing an image of the birds eye view.
    """
    # EXTRACT THE POINTS FOR EACH AXIS
    points = np.array(points)
    x_points = points[:, 0]
    y_points = points[:, 1]
    z_points = points[:, 2]

    # FILTER - To return only indices of points within desired cube
    # Three filters for: Front-to-back, side-to-side, and height ranges
    # Note left side is positive y axis in LIDAR coordinates
    f_filt = np.logical_and((x_points > fwd_range[0]), (x_points < fwd_range[1]))
    s_filt = np.logical_and((y_points > -side_range[1]), (y_points < -side_range[0]))
    filter = np.logical_and(f_filt, s_filt)
    indices = np.argwhere(filter).flatten()

    # KEEPERS
    x_points = x_points[indices]
    y_points = y_points[indices]
    z_points = z_points[indices]

    # CONVERT TO PIXEL POSITION VALUES - Based on resolution
    x_img = (-y_points / res).astype(np.int32)  # x axis is -y in LIDAR
    y_img = (-x_points / res).astype(np.int32)  # y axis is -x in LIDAR

    # SHIFT PIXELS TO HAVE MINIMUM BE (0,0)
    # floor & ceil used to prevent anything being rounded to below 0 after shift
    x_img -= int(np.floor(side_range[0] / res))
    y_img += int(np.ceil(fwd_range[1] / res))

    # CLIP HEIGHT VALUES - to between min and max heights
    pixel_values = np.clip(a=z_points,
                           a_min=height_range[0],
                           a_max=height_range[1])

    # RESCALE THE HEIGHT VALUES - to be between the range 0-255
    pixel_values = scale_to_255(pixel_values,
                                min=height_range[0],
                                max=height_range[1])

    # INITIALIZE EMPTY ARRAY - of the dimensions we want
    x_max = 1 + int((side_range[1] - side_range[0]) / res)
    y_max = 1 + int((fwd_range[1] - fwd_range[0]) / res)
    im = np.zeros([y_max, x_max], dtype=np.uint8)

    # FILL PIXEL VALUES IN IMAGE ARRAY
    im[y_img, x_img] = pixel_values

    return im


def read_pcd(pcd_path):
    lines = []
    num_points = None

    with open(pcd_path, 'r') as f:
        for line in f:
            lines.append(line.strip())
            if line.startswith('POINTS'):
                num_points = int(line.split()[-1])
    assert num_points is not None

    points = []
    for line in lines[-num_points:]:
        x, y, z, i = list(map(float, line.split()))
        #这里没有把i放进去，也是为了后面 x, y, z 做矩阵变换的时候方面
        #但这个理解我选择保留， 因为可能把i放进去也不影响代码的简易程度
        points.append((np.array([x, y, z, i])))

    return points


def load_pcd_data(file_path):
	pts = []
	f = open(file_path, 'r')
	data = f.readlines()
 
	f.close()
	line = data[9]
	# print line
	line = line.strip('\n')
	i = line.split(' ')
	pts_num = eval(i[-1])
	for line in data[11:]:
		line = line.strip('\n')
		xyzargb = line.split(' ')
		x, y, z = [eval(i) for i in xyzargb[:3]]
		argb = xyzargb[-1]
		# print type(bgra)
		argb = bin(eval(argb))[2:]
		a, r, g, b = [int(argb[8 * i:8 * i + 8], 2) for i in range(4)]
		pts.append([x, y, z, a, r, g, b])
 
	assert len(pts) == pts_num
	res = np.zeros((pts_num, len(pts[0])), dtype=np.float)
	for i in range(pts_num):
		res[i] = pts[i]
	# x = np.zeros([np.array(t) for t in pts])
	return res


def o3d_read_pcd(file_path):
	pcd = o3d.io.read_point_cloud(file_path)
	print(np.asarray(pcd.points))
	colors = np.asarray(pcd.colors) * 255
	points = np.asarray(pcd.points)
	print(points.shape, colors.shape)
    # t = np.concatenate([points, colors], axis=-1)
	return np.concatenate([points, colors], axis=-1)


def pltshowimg(im):
    #结果展示
    plt.rcParams['font.sans-serif'] = ['SimHei']  # 中文乱码
    # plt.subplot(121)
    #imshow()对图像进行处理，画出图像，show()进行图像显示
    plt.imshow(im, cmap="spectral", vmin=0, vmax=255)
    
    plt.title('图像1')
    #不显示坐标轴
    plt.axis('off')

    # #设置子图默认的间距
    plt.tight_layout()
    #显示图像
    plt.show()


def PILshowImage(img):
    im2 = Image.fromarray(img)
    im2.show()


if __name__=="__main__":
    points = o3d_read_pcd("/home/colinkang/MyFolder/StudyFolder/gstramerstudy/point2image/test.pcd")
    im = point_cloud_2_birdseye(points)
    # PILshowImage(im)
    # io.imshow(im)
    # io.show()
    pltshowimg(im)
    input()
    print ("Hello, Python!")