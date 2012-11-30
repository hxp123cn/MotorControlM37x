/* THE SOURCE CODE AND ITS
 * RELATED DOCUMENTATION IS PROVIDED "AS IS". TOSHIBA CORPORATION MAKES NO OTHER
 * WARRANTY OF ANY KIND, WHETHER EXPRESS, IMPLIED OR, STATUTORY AND DISCLAIMS ANY
 * AND ALL IMPLIED WARRANTIES OF MERCHANTABILITY, SATISFACTORY QUALITY, NON
 * INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE. THE SOURCE CODE AND
 * DOCUMENTATION MAY INCLUDE ERRORS. TOSHIBA CORPORATION RESERVES THE RIGHT TO
 * INCORPORATE MODIFICATIONS TO THE SOURCE CODE IN LATER REVISIONS OF IT, AND TO
 * MAKE IMPROVEMENTS OR CHANGES IN THE DOCUMENTATION OR THE PRODUCTS OR
 * TECHNOLOGIES DESCRIBED THEREIN AT ANY TIME. TOSHIBA CORPORATION SHALL NOT BE
 * LIABLE FOR ANY DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGE OR LIABILITY ARISING
 * FROM YOUR USE OF THE SOURCE CODE OR ANY DOCUMENTATION, INCLUDING BUT NOT
 * LIMITED TO, LOST REVENUES, DATA OR PROFITS, DAMAGES OF ANY SPECIAL, INCIDENTAL
 * OR CONSEQUENTIAL NATURE, PUNITIVE DAMAGES, LOSS OF PROPERTY OR LOSS OF PROFITS
 * ARISING OUT OF OR IN CONNECTION WITH THIS AGREEMENT, OR BEING UNUSABLE, EVEN IF
 * ADVISED OF THE POSSIBILITY OR PROBABILITY OF SUCH DAMAGES AND WHETHER A CLAIM
 * FOR SUCH DAMAGE IS BASED UPON WARRANTY, CONTRACT, TORT, NEGLIGENCE OR
 * OTHERWISE. (C)Copyright TOSHIBA CORPORATION 2011 All rights reserved
 */

#ifndef _ADC_H_
#define _ADC_H_

/*! \brief Shunt type be used
 *
 *  This enumaration is for selecting between the usage of a 1-shunt or 3-shunt 
 *  solution
 */
typedef enum 
{
  CURRENT_SHUNT_1 = 1,                                                          /*!< Channel is using 1-shunt solution */
  CURRENT_SHUNT_3 = 3,                                                          /*!< Channel is using 3-shunt solution */
  CURRENT_SENSOR_2= 2,                                                          /*!< Channel is using 2 sensor solution */
} CURRENT_MEASUREMENT;


typedef enum 
{
  CURRENT_SENSOR_NORMAL = 0,                                                    /*!< Channel is using 1-shunt solution */
  CURRENT_SENSOR_INVERTED = 1,                                                  /*!< Channel is using 3-shunt solution */
} CURRENT_SENSOR_ORIENTATION;

void ADC_Init (uint8_t channel_number, CURRENT_MEASUREMENT mesurement_type);
#endif
