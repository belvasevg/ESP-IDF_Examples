#define SDA_PORT 27
#define SCL_PORT 12
#define SDA_PULLUP_STATE 0x01
#define SCL_PULLUP_STATE 0x01

uint32_t i2c_clk_speed = 100000;
static const char* i2c_log = "I2C control";