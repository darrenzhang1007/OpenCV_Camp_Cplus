import cv2
import numpy as np
import sys
import time

if len(sys.argv) > 1:
    inputImage = cv2.imread(sys.argv[1])
else:
    inputImage = cv2.imread("H:/OpenCV_Camp_Cplus/data/images/QRcode.jpg")


def display(im, Bbox, end_time):
    """
    # Display barcode and QR code location
    :param im: input data
    :param Bbox: bbox 坐标
    :param end_time: 消耗的时间

    :return: no return; draw bbox in origin img
    """
    n = len(Bbox)
    for j in range(n):
        cv2.line(im, tuple(Bbox[j][0]), tuple(Bbox[(j + 1) % n][0]), (255, 0, 0), 3)
    im = cv2.putText(im, str(round(end_time * 1000, 2)) + ' ms', (15, 30), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 0, 255), 2)

    # Display results
    cv2.imshow("Results", im)


# QR码 检测
qrDecoder = cv2.QRCodeDetector()

# Detect and decode the QRCode
start_time = time.time()
data, bbox, rectifiedImage = qrDecoder.detectAndDecode(inputImage)
end_time = time.time() - start_time

if len(data) > 0:
    print("Decoded Data : {}".format(data))
    display(inputImage, bbox, end_time)
    rectifiedImage = np.uint8(rectifiedImage)
    cv2.imshow("Rectified QRCode", rectifiedImage)
else:
    print("QR Code not detected")
    cv2.imshow("Results", inputImage)

cv2.waitKey(0)
cv2.destroyAllWindows()
