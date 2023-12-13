from face import *
from serial_conn import *
def main():
    open_serial()
    while True:
        pixel_data = read_msg()
        pixel_data = pixel_data.replace(b'Pressed\n',b'')
        pixel_data = pixel_data.replace(b'\nStop',b'')

        pixel_2_data(pixel_data)
        time.sleep(1)
        height = Find_face('output1.jpeg')
        print("Head center position is at: ", height, " pixels")
        if(height == 0):

            print('No face detected')
            send_msg(0)
            continue

        height = 15+ height/240*10
        height = int(height)
        print("height: ", height)
        

        send_msg(height)
        print("\n\n")
    
if __name__ == "__main__":
    main()

