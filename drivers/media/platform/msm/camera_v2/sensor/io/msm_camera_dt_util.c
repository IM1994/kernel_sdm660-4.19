// SPDX-License-Identifier: GPL-2.0-only
/* Copyright (c) 2013-2020 The Linux Foundation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include "msm_camera_dt_util.h"
#include "msm_camera_io_util.h"
#include "msm_camera_i2c_mux.h"
#include "msm_cci.h"

#define CAM_SENSOR_PINCTRL_STATE_SLEEP "cam_suspend"
#define CAM_SENSOR_PINCTRL_STATE_DEFAULT "cam_default"
/*#define CONFIG_MSM_CAMERA_DT_DEBUG*/

#define VALIDATE_VOLTAGE(min, max, config_val) ((config_val) && \
	(config_val >= min) && (config_val <= max))

#undef CDBG
#define CDBG(fmt, args...) pr_debug(fmt, ##args)

int msm_camera_fill_vreg_params(struct camera_vreg_t *cam_vreg,
	int num_vreg, struct msm_sensor_power_setting *power_setting,
	uint16_t power_setting_size)
{
	uint16_t i = 0;
	int      j = 0;

	/* Validate input parameters */
	if (!cam_vreg || !power_setting) {
		pr_err("%s:%d failed: cam_vreg %pK power_setting %pK\n",
			__func__, __LINE__,  cam_vreg, power_setting);
		return -EINVAL;
	}

	/* Validate size of num_vreg */
	if (num_vreg <= 0) {
		pr_err("failed: num_vreg %d\n", num_vreg);
		return -EINVAL;
	}

	for (i = 0; i < power_setting_size; i++) {
		if (power_setting[i].seq_type != SENSOR_VREG)
			continue;

		switch (power_setting[i].seq_val) {
		case CAM_VDIG:
			for (j = 0; j < num_vreg; j++) {
				if (!strcmp(cam_vreg[j].reg_name, "cam_vdig")) {
					CDBG("%s:%d i %d j %d cam_vdig\n",
						__func__, __LINE__, i, j);
					power_setting[i].seq_val = j;
					if (VALIDATE_VOLTAGE(
						cam_vreg[j].min_voltage,
						cam_vreg[j].max_voltage,
						power_setting[i].config_val)) {
						cam_vreg[j].min_voltage =
						cam_vreg[j].max_voltage =
						power_setting[i].config_val;
					}
					break;
				}
			}
			if (j == num_vreg)
				power_setting[i].seq_val = INVALID_VREG;
			break;

		case CAM_VIO:
			for (j = 0; j < num_vreg; j++) {
				if (!strcmp(cam_vreg[j].reg_name, "cam_vio")) {
					CDBG("%s:%d i %d j %d cam_vio\n",
						__func__, __LINE__, i, j);
					power_setting[i].seq_val = j;
					if (VALIDATE_VOLTAGE(
						cam_vreg[j].min_voltage,
						cam_vreg[j].max_voltage,
						power_setting[i].config_val)) {
						cam_vreg[j].min_voltage =
						cam_vreg[j].max_voltage =
						power_setting[i].config_val;
					}
					break;
				}
			}
			if (j == num_vreg)
				power_setting[i].seq_val = INVALID_VREG;
			break;

		case CAM_VANA:
			for (j = 0; j < num_vreg; j++) {
				if (!strcmp(cam_vreg[j].reg_name, "cam_vana")) {
					CDBG("%s:%d i %d j %d cam_vana\n",
						__func__, __LINE__, i, j);
					power_setting[i].seq_val = j;
					if (VALIDATE_VOLTAGE(
						cam_vreg[j].min_voltage,
						cam_vreg[j].max_voltage,
						power_setting[i].config_val)) {
						cam_vreg[j].min_voltage =
						cam_vreg[j].max_voltage =
						power_setting[i].config_val;
					}
					break;
				}
			}
			if (j == num_vreg)
				power_setting[i].seq_val = INVALID_VREG;
			break;

		case CAM_VAF:
			for (j = 0; j < num_vreg; j++) {
				if (!strcmp(cam_vreg[j].reg_name, "cam_vaf")) {
					CDBG("%s:%d i %d j %d cam_vaf\n",
						__func__, __LINE__, i, j);
					power_setting[i].seq_val = j;
					if (VALIDATE_VOLTAGE(
						cam_vreg[j].min_voltage,
						cam_vreg[j].max_voltage,
						power_setting[i].config_val)) {
						cam_vreg[j].min_voltage =
						cam_vreg[j].max_voltage =
						power_setting[i].config_val;
					}
					break;
				}
			}
			if (j == num_vreg)
				power_setting[i].seq_val = INVALID_VREG;
			break;

		case CAM_V_CUSTOM1:
			for (j = 0; j < num_vreg; j++) {
				if (!strcmp(cam_vreg[j].reg_name,
					"cam_v_custom1")) {
					CDBG("%s:%d i %d j %d cam_vcustom1\n",
						__func__, __LINE__, i, j);
					power_setting[i].seq_val = j;
					if (VALIDATE_VOLTAGE(
						cam_vreg[j].min_voltage,
						cam_vreg[j].max_voltage,
						power_setting[i].config_val)) {
						cam_vreg[j].min_voltage =
						cam_vreg[j].max_voltage =
						power_setting[i].config_val;
					}
					break;
				}
			}
			if (j == num_vreg)
				power_setting[i].seq_val = INVALID_VREG;
			break;
		case CAM_V_CUSTOM2:
			for (j = 0; j < num_vreg; j++) {
				if (!strcmp(cam_vreg[j].reg_name,
					"cam_v_custom2")) {
					CDBG("%s:%d i %d j %d cam_vcustom2\n",
						__func__, __LINE__, i, j);
					power_setting[i].seq_val = j;
					if (VALIDATE_VOLTAGE(
						cam_vreg[j].min_voltage,
						cam_vreg[j].max_voltage,
						power_setting[i].config_val)) {
						cam_vreg[j].min_voltage =
						cam_vreg[j].max_voltage =
						power_setting[i].config_val;
					}
					break;
				}
			}
			if (j == num_vreg)
				power_setting[i].seq_val = INVALID_VREG;
			break;

		default:
			pr_err("%s:%d invalid seq_val %d\n", __func__,
				__LINE__, power_setting[i].seq_val);
			break;
		}
	}
	return 0;
}

int msm_sensor_get_sub_module_index(struct device_node *of_node,
				    struct  msm_sensor_info_t **s_info)
{
	int rc = 0, i = 0;
	uint32_t val = 0, count = 0;
	uint32_t *val_array = NULL;
	struct device_node *src_node = NULL;
	struct msm_sensor_info_t *sensor_info;

	sensor_info = kzalloc(sizeof(*sensor_info), GFP_KERNEL);
	if (!sensor_info)
		return -ENOMEM;
	for (i = 0; i < SUB_MODULE_MAX; i++) {
		sensor_info->subdev_id[i] = -1;
		/* Subdev expose additional interface for same sub module*/
		sensor_info->subdev_intf[i] = -1;
	}

	src_node = of_parse_phandle(of_node, "qcom,actuator-src", 0);
	if (!src_node) {
		CDBG("%s:%d src_node NULL\n", __func__, __LINE__);
	} else {
		rc = of_property_read_u32(src_node, "cell-index", &val);
		CDBG("%s qcom,actuator cell index %d, rc %d\n", __func__,
			val, rc);
		if (rc < 0) {
			pr_err("%s failed %d\n", __func__, __LINE__);
			goto ERROR;
		}
		sensor_info->subdev_id[SUB_MODULE_ACTUATOR] = val;
		of_node_put(src_node);
		src_node = NULL;
	}

	src_node = of_parse_phandle(of_node, "qcom,ois-src", 0);
	if (!src_node) {
		CDBG("%s:%d src_node NULL\n", __func__, __LINE__);
	} else {
		rc = of_property_read_u32(src_node, "cell-index", &val);
		CDBG("%s qcom,ois cell index %d, rc %d\n", __func__,
			val, rc);
		if (rc < 0) {
			pr_err("%s failed %d\n", __func__, __LINE__);
			goto ERROR;
		}
		sensor_info->subdev_id[SUB_MODULE_OIS] = val;
		of_node_put(src_node);
		src_node = NULL;
	}

	src_node = of_parse_phandle(of_node, "qcom,eeprom-src", 0);
	if (!src_node) {
		CDBG("%s:%d eeprom src_node NULL\n", __func__, __LINE__);
	} else {
		rc = of_property_read_u32(src_node, "cell-index", &val);
		CDBG("%s qcom,eeprom cell index %d, rc %d\n", __func__,
			val, rc);
		if (rc < 0) {
			pr_err("%s failed %d\n", __func__, __LINE__);
			goto ERROR;
		}
		sensor_info->subdev_id[SUB_MODULE_EEPROM] = val;
		of_node_put(src_node);
		src_node = NULL;
	}

	rc = of_property_read_u32(of_node, "qcom,eeprom-sd-index", &val);
	if (rc != -EINVAL) {
		CDBG("%s qcom,eeprom-sd-index %d, rc %d\n", __func__, val, rc);
		if (rc < 0) {
			pr_err("%s:%d failed rc %d\n", __func__, __LINE__, rc);
			goto ERROR;
		}
		sensor_info->subdev_id[SUB_MODULE_EEPROM] = val;
	} else {
		rc = 0;
	}

	src_node = of_parse_phandle(of_node, "qcom,led-flash-src", 0);
	if (!src_node) {
		CDBG("%s:%d src_node NULL\n", __func__, __LINE__);
	} else {
		rc = of_property_read_u32(src_node, "cell-index", &val);
		CDBG("%s qcom,led flash cell index %d, rc %d\n", __func__,
			val, rc);
		if (rc < 0) {
			pr_err("%s:%d failed %d\n", __func__, __LINE__, rc);
			goto ERROR;
		}
		sensor_info->subdev_id[SUB_MODULE_LED_FLASH] = val;
		of_node_put(src_node);
		src_node = NULL;
	}

	src_node = of_parse_phandle(of_node, "qcom,ir-led-src", 0);
	if (!src_node) {
		CDBG("%s:%d src_node NULL\n", __func__, __LINE__);
	} else {
		rc = of_property_read_u32(src_node, "cell-index", &val);
		CDBG("%s qcom,ir led cell index %d, rc %d\n", __func__,
			val, rc);
		if (rc < 0) {
			pr_err("%s:%d failed %d\n", __func__, __LINE__, rc);
			goto ERROR;
		}
		sensor_info->subdev_id[SUB_MODULE_IR_LED] = val;
		of_node_put(src_node);
		src_node = NULL;
	}

	src_node = of_parse_phandle(of_node, "qcom,ir-cut-src", 0);
	if (!src_node) {
		CDBG("%s:%d src_node NULL\n", __func__, __LINE__);
	} else {
		rc = of_property_read_u32(src_node, "cell-index", &val);
		CDBG("%s qcom,ir cut cell index %d, rc %d\n", __func__,
			val, rc);
		if (rc < 0) {
			pr_err("%s:%d failed %d\n", __func__, __LINE__, rc);
			goto ERROR;
		}
		sensor_info->subdev_id[SUB_MODULE_IR_CUT] = val;
		of_node_put(src_node);
		src_node = NULL;
	}

	rc = of_property_read_u32(of_node, "qcom,strobe-flash-sd-index", &val);
	if (rc != -EINVAL) {
		CDBG("%s qcom,strobe-flash-sd-index %d, rc %d\n", __func__,
			val, rc);
		if (rc < 0) {
			pr_err("%s:%d failed rc %d\n", __func__, __LINE__, rc);
			goto ERROR;
		}
		sensor_info->subdev_id[SUB_MODULE_STROBE_FLASH] = val;
	} else {
		rc = 0;
	}

	if (of_get_property(of_node, "qcom,csiphy-sd-index", &count)) {
		count /= sizeof(uint32_t);
		if (count > 2) {
			pr_err("%s qcom,csiphy-sd-index count %d > 2\n",
				__func__, count);
			goto ERROR;
		}
		val_array = kcalloc(count, sizeof(uint32_t), GFP_KERNEL);
		if (!val_array) {
			rc = -ENOMEM;
			goto ERROR;
		}

		rc = of_property_read_u32_array(of_node, "qcom,csiphy-sd-index",
			val_array, count);
		if (rc < 0) {
			pr_err("%s failed %d\n", __func__, __LINE__);
			kfree(val_array);
			goto ERROR;
		}
		for (i = 0; i < count; i++) {
			sensor_info->subdev_id[SUB_MODULE_CSIPHY + i] =
								val_array[i];
			CDBG("%s csiphy_core[%d] = %d\n",
				__func__, i, val_array[i]);
		}
		kfree(val_array);
	} else {
		pr_err("%s:%d qcom,csiphy-sd-index not present\n", __func__,
			__LINE__);
		rc = -EINVAL;
		goto ERROR;
	}

	if (of_get_property(of_node, "qcom,csid-sd-index", &count)) {
		count /= sizeof(uint32_t);
		if (count > 2) {
			pr_err("%s qcom,csid-sd-index count %d > 2\n",
				__func__, count);
			rc = -EINVAL;
			goto ERROR;
		}
		val_array = kcalloc(count, sizeof(uint32_t), GFP_KERNEL);
		if (!val_array) {
			rc = -ENOMEM;
			goto ERROR;
		}

		rc = of_property_read_u32_array(of_node, "qcom,csid-sd-index",
			val_array, count);
		if (rc < 0) {
			pr_err("%s failed %d\n", __func__, __LINE__);
			kfree(val_array);
			goto ERROR;
		}
		for (i = 0; i < count; i++) {
			sensor_info->subdev_id
				[SUB_MODULE_CSID + i] = val_array[i];
			CDBG("%s csid_core[%d] = %d\n",
				__func__, i, val_array[i]);
		}
		kfree(val_array);
	} else {
		pr_err("%s:%d qcom,csid-sd-index not present\n", __func__,
			__LINE__);
		rc = -EINVAL;
		goto ERROR;
	}

	*s_info = sensor_info;
	return rc;
ERROR:
	kfree(sensor_info);
	return rc;
}

int msm_sensor_get_dt_actuator_data(struct device_node *of_node,
				    struct msm_actuator_info **act_info)
{
	int rc = 0;
	uint32_t val = 0;
	struct msm_actuator_info *actuator_info;

	rc = of_property_read_u32(of_node, "qcom,actuator-cam-name", &val);
	CDBG("%s qcom,actuator-cam-name %d, rc %d\n", __func__, val, rc);
	if (rc < 0)
		return 0;

	actuator_info = kzalloc(sizeof(*actuator_info), GFP_KERNEL);
	if (!actuator_info) {
		rc = -ENOMEM;
		goto ERROR;
	}

	actuator_info->cam_name = val;

	rc = of_property_read_u32(of_node, "qcom,actuator-vcm-pwd", &val);
	CDBG("%s qcom,actuator-vcm-pwd %d, rc %d\n", __func__, val, rc);
	if (!rc)
		actuator_info->vcm_pwd = val;

	rc = of_property_read_u32(of_node, "qcom,actuator-vcm-enable", &val);
	CDBG("%s qcom,actuator-vcm-enable %d, rc %d\n", __func__, val, rc);
	if (!rc)
		actuator_info->vcm_enable = val;

	*act_info = actuator_info;
	return 0;
ERROR:
	kfree(actuator_info);
	return rc;
}

int msm_sensor_get_dt_csi_data(struct device_node *of_node,
	struct msm_camera_csi_lane_params **csi_lane_params)
{
	int rc = 0;
	uint32_t val = 0;
	struct msm_camera_csi_lane_params *clp;

	clp = kzalloc(sizeof(*clp), GFP_KERNEL);
	if (!clp)
		return -ENOMEM;
	*csi_lane_params = clp;

	rc = of_property_read_u32(of_node, "qcom,csi-lane-assign", &val);
	CDBG("%s qcom,csi-lane-assign 0x%x, rc %d\n", __func__, val, rc);
	if (rc < 0) {
		pr_err("%s failed %d\n", __func__, __LINE__);
		goto ERROR;
	}
	clp->csi_lane_assign = val;

	rc = of_property_read_u32(of_node, "qcom,csi-lane-mask", &val);
	CDBG("%s qcom,csi-lane-mask 0x%x, rc %d\n", __func__, val, rc);
	if (rc < 0) {
		pr_err("%s failed %d\n", __func__, __LINE__);
		goto ERROR;
	}
	clp->csi_lane_mask = val;

	return rc;
ERROR:
	kfree(clp);
	return rc;
}

int msm_camera_get_dt_power_setting_data(struct device_node *of_node,
	struct camera_vreg_t *cam_vreg, int num_vreg,
	struct msm_camera_power_ctrl_t *power_info)
{
	int rc = 0, i, j;
	int count = 0;
	const char *seq_name = NULL;
	uint32_t *array = NULL;
	struct msm_sensor_power_setting *ps;

	struct msm_sensor_power_setting *power_setting;
	uint16_t *power_setting_size, size = 0;
	bool need_reverse = false;

	if (!power_info)
		return -EINVAL;

	power_setting = power_info->power_setting;
	power_setting_size = &power_info->power_setting_size;

	count = of_property_count_strings(of_node, "qcom,cam-power-seq-type");
	*power_setting_size = count;

	CDBG("%s qcom,cam-power-seq-type count %d\n", __func__, count);

	if (count <= 0)
		return 0;

	ps = kcalloc(count, sizeof(*ps), GFP_KERNEL);
	if (!ps)
		return -ENOMEM;
	power_setting = ps;
	power_info->power_setting = ps;

	for (i = 0; i < count; i++) {
		rc = of_property_read_string_index(of_node,
			"qcom,cam-power-seq-type", i,
			&seq_name);
		CDBG("%s seq_name[%d] = %s\n", __func__, i,
			seq_name);
		if (rc < 0) {
			pr_err("%s failed %d\n", __func__, __LINE__);
			goto ERROR1;
		}
		if (!strcmp(seq_name, "sensor_vreg")) {
			ps[i].seq_type = SENSOR_VREG;
			CDBG("%s:%d seq_type[%d] %d\n", __func__, __LINE__,
				i, ps[i].seq_type);
		} else if (!strcmp(seq_name, "sensor_gpio")) {
			ps[i].seq_type = SENSOR_GPIO;
			CDBG("%s:%d seq_type[%d] %d\n", __func__, __LINE__,
				i, ps[i].seq_type);
		} else if (!strcmp(seq_name, "sensor_clk")) {
			ps[i].seq_type = SENSOR_CLK;
			CDBG("%s:%d seq_type[%d] %d\n", __func__, __LINE__,
				i, ps[i].seq_type);
		} else if (!strcmp(seq_name, "sensor_i2c_mux")) {
			ps[i].seq_type = SENSOR_I2C_MUX;
			CDBG("%s:%d seq_type[%d] %d\n", __func__, __LINE__,
				i, ps[i].seq_type);
		} else {
			CDBG("%s: unrecognized seq-type\n", __func__);
			rc = -EILSEQ;
			goto ERROR1;
		}
	}


	for (i = 0; i < count; i++) {
		rc = of_property_read_string_index(of_node,
			"qcom,cam-power-seq-val", i,
			&seq_name);
		CDBG("%s seq_name[%d] = %s\n", __func__, i,
			seq_name);
		if (rc < 0) {
			pr_err("%s failed %d\n", __func__, __LINE__);
			goto ERROR1;
		}
		switch (ps[i].seq_type) {
		case SENSOR_VREG:
			for (j = 0; j < num_vreg; j++) {
				if (!strcmp(seq_name, cam_vreg[j].reg_name))
					break;
			}
			if (j < num_vreg)
				ps[i].seq_val = j;
			else
				rc = -EILSEQ;
			break;
		case SENSOR_GPIO:
			if (!strcmp(seq_name, "sensor_gpio_reset"))
				ps[i].seq_val = SENSOR_GPIO_RESET;
			else if (!strcmp(seq_name, "sensor_gpio_standby"))
				ps[i].seq_val = SENSOR_GPIO_STANDBY;
			else if (!strcmp(seq_name, "sensor_gpio_vdig"))
				ps[i].seq_val = SENSOR_GPIO_VDIG;
			else if (!strcmp(seq_name, "sensor_gpio_vana"))
				ps[i].seq_val = SENSOR_GPIO_VANA;
			else if (!strcmp(seq_name, "sensor_gpio_vaf"))
				ps[i].seq_val = SENSOR_GPIO_VAF;
			else if (!strcmp(seq_name, "sensor_gpio_vio"))
				ps[i].seq_val = SENSOR_GPIO_VIO;
			else if (!strcmp(seq_name, "sensor_gpio_custom1"))
				ps[i].seq_val = SENSOR_GPIO_CUSTOM1;
			else if (!strcmp(seq_name, "sensor_gpio_custom2"))
				ps[i].seq_val = SENSOR_GPIO_CUSTOM2;
			else if (!strcmp(seq_name, "sensor_gpio_custom3"))
				ps[i].seq_val = SENSOR_GPIO_CUSTOM3;
			else
				rc = -EILSEQ;
			break;
		case SENSOR_CLK:
			if (!strcmp(seq_name, "sensor_cam_mclk"))
				ps[i].seq_val = SENSOR_CAM_MCLK;
			else if (!strcmp(seq_name, "sensor_cam_clk"))
				ps[i].seq_val = SENSOR_CAM_CLK;
			else
				rc = -EILSEQ;
			break;
		case SENSOR_I2C_MUX:
			if (!strcmp(seq_name, "none"))
				ps[i].seq_val = 0;
			else
				rc = -EILSEQ;
			break;
		default:
			rc = -EILSEQ;
			break;
		}
		if (rc < 0) {
			CDBG("%s: unrecognized seq-val\n", __func__);
			goto ERROR1;
		}
	}

	array = kcalloc(count, sizeof(uint32_t), GFP_KERNEL);
	if (!array) {
		rc = -ENOMEM;
		goto ERROR1;
	}


	rc = of_property_read_u32_array(of_node, "qcom,cam-power-seq-cfg-val",
		array, count);
	if (rc < 0) {
		pr_err("%s failed %d\n", __func__, __LINE__);
		goto ERROR2;
	}
	for (i = 0; i < count; i++) {
		if (ps[i].seq_type == SENSOR_GPIO) {
			if (array[i] == 0)
				ps[i].config_val = GPIO_OUT_LOW;
			else if (array[i] == 1)
				ps[i].config_val = GPIO_OUT_HIGH;
		} else {
			ps[i].config_val = array[i];
		}
		CDBG("%s power_setting[%d].config_val = %ld\n", __func__, i,
			ps[i].config_val);
	}

	rc = of_property_read_u32_array(of_node, "qcom,cam-power-seq-delay",
		array, count);
	if (rc < 0) {
		pr_err("%s failed %d\n", __func__, __LINE__);
		goto ERROR2;
	}
	for (i = 0; i < count; i++) {
		ps[i].delay = array[i];
		CDBG("%s power_setting[%d].delay = %d\n", __func__,
			i, ps[i].delay);
	}
	kfree(array);

	size = *power_setting_size;

	if (NULL != ps && 0 != size)
		need_reverse = true;

	power_info->power_down_setting =
		kcalloc(size, sizeof(*ps), GFP_KERNEL);

	if (!power_info->power_down_setting) {
		pr_err("%s failed %d\n", __func__, __LINE__);
		rc = -ENOMEM;
		goto ERROR1;
	}

	memcpy(power_info->power_down_setting,
		ps, sizeof(*ps) * size);

	power_info->power_down_setting_size = size;

	if (need_reverse) {
		int c, end = size - 1;
		struct msm_sensor_power_setting power_down_setting_t;

		for (c = 0; c < size/2; c++) {
			power_down_setting_t =
				power_info->power_down_setting[c];
			power_info->power_down_setting[c] =
				power_info->power_down_setting[end];
			power_info->power_down_setting[end] =
				power_down_setting_t;
			end--;
		}
	}
	return rc;
ERROR2:
	kfree(array);
ERROR1:
	kfree(ps);
	power_setting_size = NULL;
	return rc;
}

int msm_camera_get_dt_gpio_req_tbl(struct device_node *of_node,
	struct msm_camera_gpio_conf *gconf, uint16_t *gpio_array,
	uint16_t gpio_array_size)
{
	int rc = 0, i = 0;
	uint32_t count = 0;
	uint32_t *val_array = NULL;

	if (!of_get_property(of_node, "qcom,gpio-req-tbl-num", &count))
		return 0;

	count /= sizeof(uint32_t);
	if (!count) {
		pr_err("%s qcom,gpio-req-tbl-num 0\n", __func__);
		return 0;
	}

	val_array = kcalloc(count, sizeof(uint32_t), GFP_KERNEL);
	if (!val_array)
		return -ENOMEM;

	gconf->cam_gpio_req_tbl = kcalloc(count, sizeof(struct gpio),
		GFP_KERNEL);
	if (!gconf->cam_gpio_req_tbl) {
		rc = -ENOMEM;
		goto ERROR1;
	}
	gconf->cam_gpio_req_tbl_size = count;

	rc = of_property_read_u32_array(of_node, "qcom,gpio-req-tbl-num",
		val_array, count);
	if (rc < 0) {
		pr_err("%s failed %d\n", __func__, __LINE__);
		goto ERROR2;
	}
	for (i = 0; i < count; i++) {
		if (val_array[i] >= gpio_array_size) {
			pr_err("%s gpio req tbl index %d invalid\n",
				__func__, val_array[i]);
			return -EINVAL;
		}
		gconf->cam_gpio_req_tbl[i].gpio = gpio_array[val_array[i]];
		CDBG("%s cam_gpio_req_tbl[%d].gpio = %d\n", __func__, i,
			gconf->cam_gpio_req_tbl[i].gpio);
	}

	rc = of_property_read_u32_array(of_node, "qcom,gpio-req-tbl-flags",
		val_array, count);
	if (rc < 0) {
		pr_err("%s failed %d\n", __func__, __LINE__);
		goto ERROR2;
	}
	for (i = 0; i < count; i++) {
		gconf->cam_gpio_req_tbl[i].flags = val_array[i];
		CDBG("%s cam_gpio_req_tbl[%d].flags = %ld\n", __func__, i,
			gconf->cam_gpio_req_tbl[i].flags);
	}

	for (i = 0; i < count; i++) {
		rc = of_property_read_string_index(of_node,
			"qcom,gpio-req-tbl-label", i,
			&gconf->cam_gpio_req_tbl[i].label);
		CDBG("%s cam_gpio_req_tbl[%d].label = %s\n", __func__, i,
			gconf->cam_gpio_req_tbl[i].label);
		if (rc < 0) {
			pr_err("%s failed %d\n", __func__, __LINE__);
			goto ERROR2;
		}
	}

	kfree(val_array);
	return rc;

ERROR2:
	kfree(gconf->cam_gpio_req_tbl);
ERROR1:
	kfree(val_array);
	gconf->cam_gpio_req_tbl_size = 0;
	return rc;
}

int msm_camera_init_gpio_pin_tbl(struct device_node *of_node,
	struct msm_camera_gpio_conf *gconf, uint16_t *gpio_array,
	uint16_t gpio_array_size)
{
	int rc = 0, val = 0;

	gconf->gpio_num_info = kzalloc(sizeof(struct msm_camera_gpio_num_info),
		GFP_KERNEL);
	if (!gconf->gpio_num_info) {
		rc = -ENOMEM;
		return rc;
	}

	rc = of_property_read_u32(of_node, "qcom,gpio-ir-p", &val);
	if (rc != -EINVAL) {
		if (rc < 0) {
			pr_err("%s:%d read qcom,gpio-ir-p failed rc %d\n",
				__func__, __LINE__, rc);
			goto ERROR;
		} else if (val >= gpio_array_size) {
			pr_err("%s:%d qcom,gpio-ir-p invalid %d\n",
				__func__, __LINE__, val);
			rc = -EINVAL;
			goto ERROR;
		}

		gconf->gpio_num_info->gpio_num[IR_CUT_FILTER_GPIO_P] =
			gpio_array[val];
		gconf->gpio_num_info->valid[IR_CUT_FILTER_GPIO_P] = 1;

		CDBG("%s qcom,gpio-ir-p %d\n", __func__,
			gconf->gpio_num_info->gpio_num[IR_CUT_FILTER_GPIO_P]);
	} else {
		rc = 0;
	}

	rc = of_property_read_u32(of_node, "qcom,gpio-ir-m", &val);
	if (rc != -EINVAL) {
		if (rc < 0) {
			pr_err("%s:%d read qcom,gpio-ir-m failed rc %d\n",
				__func__, __LINE__, rc);
			goto ERROR;
		} else if (val >= gpio_array_size) {
			pr_err("%s:%d qcom,gpio-ir-m invalid %d\n",
				__func__, __LINE__, val);
			rc = -EINVAL;
			goto ERROR;
		}

		gconf->gpio_num_info->gpio_num[IR_CUT_FILTER_GPIO_M] =
			gpio_array[val];

		gconf->gpio_num_info->valid[IR_CUT_FILTER_GPIO_M] = 1;

		CDBG("%s qcom,gpio-ir-m %d\n", __func__,
			gconf->gpio_num_info->gpio_num[IR_CUT_FILTER_GPIO_M]);
	} else {
		rc = 0;
	}

	rc = of_property_read_u32(of_node, "qcom,gpio-vana", &val);
	if (rc != -EINVAL) {
		if (rc < 0) {
			pr_err("%s:%d read qcom,gpio-vana failed rc %d\n",
				__func__, __LINE__, rc);
			goto ERROR;
		} else if (val >= gpio_array_size) {
			pr_err("%s:%d qcom,gpio-vana invalid %d\n",
				__func__, __LINE__, val);
			rc = -EINVAL;
			goto ERROR;
		}
		gconf->gpio_num_info->gpio_num[SENSOR_GPIO_VANA] =
			gpio_array[val];
		gconf->gpio_num_info->valid[SENSOR_GPIO_VANA] = 1;
		CDBG("%s qcom,gpio-vana %d\n", __func__,
			gconf->gpio_num_info->gpio_num[SENSOR_GPIO_VANA]);
	} else {
		rc = 0;
	}

	rc = of_property_read_u32(of_node, "qcom,gpio-vio", &val);
	if (rc != -EINVAL) {
		if (rc < 0) {
			pr_err("%s:%d read qcom,gpio-vio failed rc %d\n",
				__func__, __LINE__, rc);
			goto ERROR;
		} else if (val >= gpio_array_size) {
			pr_err("%s:%d qcom,gpio-vio invalid %d\n",
				__func__, __LINE__, val);
			goto ERROR;
		}
		gconf->gpio_num_info->gpio_num[SENSOR_GPIO_VIO] =
			gpio_array[val];
		gconf->gpio_num_info->valid[SENSOR_GPIO_VIO] = 1;
		CDBG("%s qcom,gpio-vio %d\n", __func__,
			gconf->gpio_num_info->gpio_num[SENSOR_GPIO_VIO]);
	} else {
		rc = 0;
	}

	rc = of_property_read_u32(of_node, "qcom,gpio-vaf", &val);
	if (rc != -EINVAL) {
		if (rc < 0) {
			pr_err("%s:%d read qcom,gpio-vaf failed rc %d\n",
				__func__, __LINE__, rc);
			goto ERROR;
		} else if (val >= gpio_array_size) {
			pr_err("%s:%d qcom,gpio-vaf invalid %d\n",
				__func__, __LINE__, val);
			rc = -EINVAL;
			goto ERROR;
		}
		gconf->gpio_num_info->gpio_num[SENSOR_GPIO_VAF] =
			gpio_array[val];
		gconf->gpio_num_info->valid[SENSOR_GPIO_VAF] = 1;
		CDBG("%s qcom,gpio-vaf %d\n", __func__,
			gconf->gpio_num_info->gpio_num[SENSOR_GPIO_VAF]);
	} else {
		rc = 0;
	}

	rc = of_property_read_u32(of_node, "qcom,gpio-vdig", &val);
	if (rc != -EINVAL) {
		if (rc < 0) {
			pr_err("%s:%d read qcom,gpio-vdig failed rc %d\n",
				__func__, __LINE__, rc);
			goto ERROR;
		} else if (val >= gpio_array_size) {
			pr_err("%s:%d qcom,gpio-vdig invalid %d\n",
				__func__, __LINE__, val);
			rc = -EINVAL;
			goto ERROR;
		}
		gconf->gpio_num_info->gpio_num[SENSOR_GPIO_VDIG] =
			gpio_array[val];
		gconf->gpio_num_info->valid[SENSOR_GPIO_VDIG] = 1;
		CDBG("%s qcom,gpio-vdig %d\n", __func__,
			gconf->gpio_num_info->gpio_num[SENSOR_GPIO_VDIG]);
	} else {
		rc = 0;
	}

	rc = of_property_read_u32(of_node, "qcom,gpio-reset", &val);
	if (rc != -EINVAL) {
		if (rc < 0) {
			pr_err("%s:%d read qcom,gpio-reset failed rc %d\n",
				__func__, __LINE__, rc);
			goto ERROR;
		} else if (val >= gpio_array_size) {
			pr_err("%s:%d qcom,gpio-reset invalid %d\n",
				__func__, __LINE__, val);
			rc = -EINVAL;
			goto ERROR;
		}
		gconf->gpio_num_info->gpio_num[SENSOR_GPIO_RESET] =
			gpio_array[val];
		gconf->gpio_num_info->valid[SENSOR_GPIO_RESET] = 1;
		CDBG("%s qcom,gpio-reset %d\n", __func__,
			gconf->gpio_num_info->gpio_num[SENSOR_GPIO_RESET]);
	} else {
		rc = 0;
	}

	rc = of_property_read_u32(of_node, "qcom,gpio-standby", &val);
	if (rc != -EINVAL) {
		if (rc < 0) {
			pr_err("%s:%d read qcom,gpio-standby failed rc %d\n",
				__func__, __LINE__, rc);
			goto ERROR;
		} else if (val >= gpio_array_size) {
			pr_err("%s:%d qcom,gpio-standby invalid %d\n",
				__func__, __LINE__, val);
			rc = -EINVAL;
			goto ERROR;
		}
		gconf->gpio_num_info->gpio_num[SENSOR_GPIO_STANDBY] =
			gpio_array[val];
		gconf->gpio_num_info->valid[SENSOR_GPIO_STANDBY] = 1;
		CDBG("%s qcom,gpio-standby %d\n", __func__,
			gconf->gpio_num_info->gpio_num[SENSOR_GPIO_STANDBY]);
	} else {
		rc = 0;
	}

	rc = of_property_read_u32(of_node, "qcom,gpio-af-pwdm", &val);
	if (rc != -EINVAL) {
		if (rc < 0) {
			pr_err("%s:%d read qcom,gpio-af-pwdm failed rc %d\n",
				__func__, __LINE__, rc);
			goto ERROR;
		} else if (val >= gpio_array_size) {
			pr_err("%s:%d qcom,gpio-af-pwdm invalid %d\n",
				__func__, __LINE__, val);
			rc = -EINVAL;
			goto ERROR;
		}
		gconf->gpio_num_info->gpio_num[SENSOR_GPIO_AF_PWDM] =
			gpio_array[val];
		gconf->gpio_num_info->valid[SENSOR_GPIO_AF_PWDM] = 1;
		CDBG("%s qcom,gpio-af-pwdm %d\n", __func__,
			gconf->gpio_num_info->gpio_num[SENSOR_GPIO_AF_PWDM]);
	} else {
		rc = 0;
	}

	rc = of_property_read_u32(of_node, "qcom,gpio-flash-en", &val);
	if (rc != -EINVAL) {
		if (rc < 0) {
			pr_err("%s:%d read qcom,gpio-flash-en failed rc %d\n",
				__func__, __LINE__, rc);
			goto ERROR;
		} else if (val >= gpio_array_size) {
			pr_err("%s:%d qcom,gpio-flash-en invalid %d\n",
				__func__, __LINE__, val);
			rc = -EINVAL;
			goto ERROR;
		}
		gconf->gpio_num_info->gpio_num[SENSOR_GPIO_FL_EN] =
			gpio_array[val];
		gconf->gpio_num_info->valid[SENSOR_GPIO_FL_EN] = 1;
		CDBG("%s qcom,gpio-flash-en %d\n", __func__,
			gconf->gpio_num_info->gpio_num[SENSOR_GPIO_FL_EN]);
	} else {
		rc = 0;
	}

	rc = of_property_read_u32(of_node, "qcom,gpio-flash-now", &val);
	if (rc != -EINVAL) {
		if (rc < 0) {
			pr_err("%s:%d read qcom,gpio-flash-now failed rc %d\n",
				__func__, __LINE__, rc);
			goto ERROR;
		} else if (val >= gpio_array_size) {
			pr_err("%s:%d qcom,gpio-flash-now invalid %d\n",
				__func__, __LINE__, val);
			rc = -EINVAL;
			goto ERROR;
		}
		gconf->gpio_num_info->gpio_num[SENSOR_GPIO_FL_NOW] =
			gpio_array[val];
		gconf->gpio_num_info->valid[SENSOR_GPIO_FL_NOW] = 1;
		CDBG("%s qcom,gpio-flash-now %d\n", __func__,
			gconf->gpio_num_info->gpio_num[SENSOR_GPIO_FL_NOW]);
	} else {
		rc = 0;
	}

	rc = of_property_read_u32(of_node, "qcom,gpio-flash-reset", &val);
	if (rc != -EINVAL) {
		if (rc < 0) {
			pr_err("%s:%dread qcom,gpio-flash-reset failed rc %d\n",
				__func__, __LINE__, rc);
			goto ERROR;
		} else if (val >= gpio_array_size) {
			pr_err("%s:%d qcom,gpio-flash-reset invalid %d\n",
				__func__, __LINE__, val);
			rc = -EINVAL;
			goto ERROR;
		}
		gconf->gpio_num_info->gpio_num[SENSOR_GPIO_FL_RESET] =
			gpio_array[val];
		gconf->gpio_num_info->valid[SENSOR_GPIO_FL_RESET] = 1;
		CDBG("%s qcom,gpio-flash-reset %d\n", __func__,
			gconf->gpio_num_info->gpio_num[SENSOR_GPIO_FL_RESET]);
	} else
		rc = 0;

	rc = of_property_read_u32(of_node, "qcom,gpio-custom1", &val);
	if (rc != -EINVAL) {
		if (rc < 0) {
			pr_err("%s:%d read qcom,gpio-custom1 failed rc %d\n",
				__func__, __LINE__, rc);
			goto ERROR;
		} else if (val >= gpio_array_size) {
			pr_err("%s:%d qcom,gpio-custom1 invalid %d\n",
				__func__, __LINE__, val);
			rc = -EINVAL;
			goto ERROR;
		}
		gconf->gpio_num_info->gpio_num[SENSOR_GPIO_CUSTOM1] =
			gpio_array[val];
		gconf->gpio_num_info->valid[SENSOR_GPIO_CUSTOM1] = 1;
		CDBG("%s qcom,gpio-custom1 %d\n", __func__,
			gconf->gpio_num_info->gpio_num[SENSOR_GPIO_CUSTOM1]);
	} else {
		rc = 0;
	}

	rc = of_property_read_u32(of_node, "qcom,gpio-custom2", &val);
	if (rc != -EINVAL) {
		if (rc < 0) {
			pr_err("%s:%d read qcom,gpio-custom2 failed rc %d\n",
				__func__, __LINE__, rc);
			goto ERROR;
		} else if (val >= gpio_array_size) {
			pr_err("%s:%d qcom,gpio-custom2 invalid %d\n",
				__func__, __LINE__, val);
			rc = -EINVAL;
			goto ERROR;
		}
		gconf->gpio_num_info->gpio_num[SENSOR_GPIO_CUSTOM2] =
			gpio_array[val];
		gconf->gpio_num_info->valid[SENSOR_GPIO_CUSTOM2] = 1;
		CDBG("%s qcom,gpio-custom2 %d\n", __func__,
			gconf->gpio_num_info->gpio_num[SENSOR_GPIO_CUSTOM2]);
	} else {
		rc = 0;
	}

	rc = of_property_read_u32(of_node, "qcom,gpio-custom3", &val);
	if (rc != -EINVAL) {
		if (rc < 0) {
			pr_err("%s:%d read qcom,gpio-custom3 failed rc %d\n",
				__func__, __LINE__, rc);
			goto ERROR;
		} else if (val >= gpio_array_size) {
			pr_err("%s:%d qcom,gpio-custom3 invalid %d\n",
				__func__, __LINE__, val);
			rc = -EINVAL;
			goto ERROR;
		}
		gconf->gpio_num_info->gpio_num[SENSOR_GPIO_CUSTOM3] =
			gpio_array[val];
		gconf->gpio_num_info->valid[SENSOR_GPIO_CUSTOM3] = 1;
		CDBG("%s qcom,gpio-custom3 %d\n", __func__,
			gconf->gpio_num_info->gpio_num[SENSOR_GPIO_CUSTOM3]);
	} else {
		rc = 0;
	}

	return rc;

ERROR:
	kfree(gconf->gpio_num_info);
	gconf->gpio_num_info = NULL;
	return rc;
}

int msm_camera_get_dt_vreg_data(struct device_node *of_node,
	struct camera_vreg_t **cam_vreg, int *num_vreg)
{
	int rc = 0, i = 0;
	int32_t count = 0;
	uint32_t *vreg_array = NULL;
	struct camera_vreg_t *vreg = NULL;
	bool custom_vreg_name =  false;

	count = of_property_count_strings(of_node, "qcom,cam-vreg-name");
	CDBG("%s qcom,cam-vreg-name count %d\n", __func__, count);

	if (!count || (count == -EINVAL)) {
		pr_err("%s:%d number of entries is 0 or not present in dts\n",
			__func__, __LINE__);
		*num_vreg = 0;
		return 0;
	}

	vreg = kcalloc(count, sizeof(*vreg), GFP_KERNEL);
	if (!vreg)
		return -ENOMEM;
	*cam_vreg = vreg;
	*num_vreg = count;
	for (i = 0; i < count; i++) {
		rc = of_property_read_string_index(of_node,
			"qcom,cam-vreg-name", i,
			&vreg[i].reg_name);
		CDBG("%s reg_name[%d] = %s\n", __func__, i,
			vreg[i].reg_name);
		if (rc < 0) {
			pr_err("%s failed %d\n", __func__, __LINE__);
			goto ERROR1;
		}
	}

	custom_vreg_name = of_property_read_bool(of_node,
		"qcom,cam-custom-vreg-name");
	if (custom_vreg_name) {
		for (i = 0; i < count; i++) {
			rc = of_property_read_string_index(of_node,
				"qcom,cam-custom-vreg-name", i,
				&vreg[i].custom_vreg_name);
			CDBG("%s sub reg_name[%d] = %s\n", __func__, i,
				vreg[i].custom_vreg_name);
			if (rc < 0) {
				pr_err("%s failed %d\n", __func__, __LINE__);
				goto ERROR1;
			}
		}
	}

	vreg_array = kcalloc(count, sizeof(uint32_t), GFP_KERNEL);
	if (!vreg_array) {
		rc = -ENOMEM;
		goto ERROR1;
	}

	for (i = 0; i < count; i++)
		vreg[i].type = VREG_TYPE_DEFAULT;

	rc = of_property_read_u32_array(of_node, "qcom,cam-vreg-type",
		vreg_array, count);
	if (rc != -EINVAL) {
		if (rc < 0) {
			pr_err("%s failed %d\n", __func__, __LINE__);
			goto ERROR2;
		} else {
			for (i = 0; i < count; i++) {
				vreg[i].type = vreg_array[i];
				CDBG("%s cam_vreg[%d].type = %d\n",
					__func__, i, vreg[i].type);
			}
		}
	} else {
		CDBG("%s:%d no qcom,cam-vreg-type entries in dts\n",
			__func__, __LINE__);
		rc = 0;
	}

	rc = of_property_read_u32_array(of_node, "qcom,cam-vreg-min-voltage",
		vreg_array, count);
	if (rc != -EINVAL) {
		if (rc < 0) {
			pr_err("%s failed %d\n", __func__, __LINE__);
			goto ERROR2;
		} else {
			for (i = 0; i < count; i++) {
				vreg[i].min_voltage = vreg_array[i];
				CDBG("%s cam_vreg[%d].min_voltage = %d\n",
					__func__, i, vreg[i].min_voltage);
			}
		}
	} else {
		CDBG("%s:%d no qcom,cam-vreg-min-voltage entries in dts\n",
			__func__, __LINE__);
		rc = 0;
	}

	rc = of_property_read_u32_array(of_node, "qcom,cam-vreg-max-voltage",
		vreg_array, count);
	if (rc != -EINVAL) {
		if (rc < 0) {
			pr_err("%s failed %d\n", __func__, __LINE__);
			goto ERROR2;
		} else {
			for (i = 0; i < count; i++) {
				vreg[i].max_voltage = vreg_array[i];
				CDBG("%s cam_vreg[%d].max_voltage = %d\n",
					__func__, i, vreg[i].max_voltage);
			}
		}
	} else {
		CDBG("%s:%d no qcom,cam-vreg-max-voltage entries in dts\n",
			__func__, __LINE__);
		rc = 0;
	}

	rc = of_property_read_u32_array(of_node, "qcom,cam-vreg-op-mode",
		vreg_array, count);
	if (rc != -EINVAL) {
		if (rc < 0) {
			pr_err("%s failed %d\n", __func__, __LINE__);
			goto ERROR2;
		} else {
			for (i = 0; i < count; i++) {
				vreg[i].op_mode = vreg_array[i];
				CDBG("%s cam_vreg[%d].op_mode = %d\n",
					__func__, i, vreg[i].op_mode);
			}
		}
	} else {
		CDBG("%s:%d no qcom,cam-vreg-op-mode entries in dts\n",
			__func__, __LINE__);
		rc = 0;
	}

	kfree(vreg_array);
	return rc;
ERROR2:
	kfree(vreg_array);
ERROR1:
	kfree(vreg);
	*num_vreg = 0;
	return rc;
}

static int msm_camera_enable_i2c_mux(struct msm_camera_i2c_conf *i2c_conf)
{
	struct v4l2_subdev *i2c_mux_sd =
		dev_get_drvdata(&i2c_conf->mux_dev->dev);
	v4l2_subdev_call(i2c_mux_sd, core, ioctl,
		VIDIOC_MSM_I2C_MUX_INIT, NULL);
	v4l2_subdev_call(i2c_mux_sd, core, ioctl,
		VIDIOC_MSM_I2C_MUX_CFG, (void *)&i2c_conf->i2c_mux_mode);
	return 0;
}

static int msm_camera_disable_i2c_mux(struct msm_camera_i2c_conf *i2c_conf)
{
	struct v4l2_subdev *i2c_mux_sd =
		dev_get_drvdata(&i2c_conf->mux_dev->dev);
	v4l2_subdev_call(i2c_mux_sd, core, ioctl,
		VIDIOC_MSM_I2C_MUX_RELEASE, NULL);
	return 0;
}

int msm_camera_pinctrl_init(
	struct msm_pinctrl_info *sensor_pctrl, struct device *dev)
{
	sensor_pctrl->pinctrl = devm_pinctrl_get(dev);
	if (IS_ERR_OR_NULL(sensor_pctrl->pinctrl)) {
		pr_err("%s:%d Getting pinctrl handle failed\n",
			__func__, __LINE__);
		return -EINVAL;
	}
	sensor_pctrl->gpio_state_active =
		pinctrl_lookup_state(sensor_pctrl->pinctrl,
				CAM_SENSOR_PINCTRL_STATE_DEFAULT);
	if (IS_ERR_OR_NULL(sensor_pctrl->gpio_state_active)) {
		pr_err("%s:%d Failed to get the active state pinctrl handle\n",
			__func__, __LINE__);
		return -EINVAL;
	}
	sensor_pctrl->gpio_state_suspend
		= pinctrl_lookup_state(sensor_pctrl->pinctrl,
				CAM_SENSOR_PINCTRL_STATE_SLEEP);
	if (IS_ERR_OR_NULL(sensor_pctrl->gpio_state_suspend)) {
		pr_err("%s:%d Failed to get the suspend state pinctrl handle\n",
				__func__, __LINE__);
		return -EINVAL;
	}
	return 0;
}

static int msm_cam_sensor_handle_reg_gpio(int seq_val,
	struct msm_camera_gpio_conf *gconf, int val)
{
	int gpio_offset = -1;

	if (!gconf) {
		pr_err("ERR:%s: Input Parameters are not proper\n", __func__);
		return -EINVAL;
	}
	CDBG("%s: %d Seq val: %d, config: %d", __func__, __LINE__,
		seq_val, val);

	switch (seq_val) {
	case CAM_VDIG:
		gpio_offset = SENSOR_GPIO_VDIG;
		break;

	case CAM_VIO:
		gpio_offset = SENSOR_GPIO_VIO;
		break;

	case CAM_VANA:
		gpio_offset = SENSOR_GPIO_VANA;
		break;

	case CAM_VAF:
		gpio_offset = SENSOR_GPIO_VAF;
		break;

	case CAM_V_CUSTOM1:
		gpio_offset = SENSOR_GPIO_CUSTOM1;
		break;

	case CAM_V_CUSTOM2:
		gpio_offset = SENSOR_GPIO_CUSTOM2;
		break;

	default:
		pr_err("%s:%d Invalid VREG seq val %d\n", __func__,
			__LINE__, seq_val);
		return -EINVAL;
	}

	CDBG("%s: %d GPIO offset: %d, seq_val: %d\n", __func__, __LINE__,
		gpio_offset, seq_val);

	if (gconf->gpio_num_info->valid[gpio_offset] == 1) {
		gpio_set_value_cansleep(
			gconf->gpio_num_info->gpio_num
			[gpio_offset], val);
	}
	return 0;
}

int32_t msm_sensor_driver_get_gpio_data(
	struct msm_camera_gpio_conf **gpio_conf,
	struct device_node *of_node)
{
	int32_t                      rc = 0, i = 0;
	uint16_t                    *gpio_array = NULL;
	int16_t                     gpio_array_size = 0;
	struct msm_camera_gpio_conf *gconf = NULL;

	/* Validate input parameters */
	if (!of_node) {
		pr_err("failed: invalid param of_node %pK\n", of_node);
		return -EINVAL;
	}

	gpio_array_size = of_gpio_count(of_node);
	CDBG("gpio count %d\n", gpio_array_size);
	if (gpio_array_size <= 0)
		return 0;

	gconf = kzalloc(sizeof(struct msm_camera_gpio_conf),
		GFP_KERNEL);
	if (!gconf)
		return -ENOMEM;

	*gpio_conf = gconf;

	gpio_array = kcalloc(gpio_array_size, sizeof(uint16_t), GFP_KERNEL);
	if (!gpio_array)
		goto FREE_GPIO_CONF;

	for (i = 0; i < gpio_array_size; i++) {
		gpio_array[i] = of_get_gpio(of_node, i);
		CDBG("gpio_array[%d] = %d", i, gpio_array[i]);
	}
	rc = msm_camera_get_dt_gpio_req_tbl(of_node, gconf, gpio_array,
		gpio_array_size);
	if (rc < 0) {
		pr_err("failed in msm_camera_get_dt_gpio_req_tbl\n");
		goto FREE_GPIO_CONF;
	}

	rc = msm_camera_init_gpio_pin_tbl(of_node, gconf, gpio_array,
		gpio_array_size);
	if (rc < 0) {
		pr_err("failed in msm_camera_init_gpio_pin_tbl\n");
		goto FREE_GPIO_REQ_TBL;
	}
	kfree(gpio_array);
	return rc;

FREE_GPIO_REQ_TBL:
	kfree(gconf->cam_gpio_req_tbl);
FREE_GPIO_CONF:
	kfree(gconf);
	kfree(gpio_array);
	*gpio_conf = NULL;
	return rc;
}

int msm_camera_power_up(struct msm_camera_power_ctrl_t *ctrl,
	enum msm_camera_device_type_t device_type,
	struct msm_camera_i2c_client *sensor_i2c_client)
{
	int rc = 0, index = 0, no_gpio = 0, ret = 0;
	struct msm_sensor_power_setting *power_setting = NULL;

	CDBG("%s:%d\n", __func__, __LINE__);
	if (!ctrl || !sensor_i2c_client) {
		pr_err("failed ctrl %pK sensor_i2c_client %pK\n", ctrl,
			sensor_i2c_client);
		return -EINVAL;
	}
	if (ctrl->gpio_conf->cam_gpiomux_conf_tbl != NULL)
		pr_err("%s:%d mux install\n", __func__, __LINE__);

	ret = msm_camera_pinctrl_init(&(ctrl->pinctrl_info), ctrl->dev);
	if (ret < 0) {
		pr_err("%s:%d Initialization of pinctrl failed\n",
				__func__, __LINE__);
		ctrl->cam_pinctrl_status = 0;
	} else {
		ctrl->cam_pinctrl_status = 1;
	}
	rc = msm_camera_request_gpio_table(
		ctrl->gpio_conf->cam_gpio_req_tbl,
		ctrl->gpio_conf->cam_gpio_req_tbl_size, 1);
	if (rc < 0)
		no_gpio = rc;
	if (ctrl->cam_pinctrl_status) {
		ret = pinctrl_select_state(ctrl->pinctrl_info.pinctrl,
			ctrl->pinctrl_info.gpio_state_active);
		if (ret)
			pr_err("%s:%d cannot set pin to active state\n",
				__func__, __LINE__);
	}
	for (index = 0; index < ctrl->power_setting_size; index++) {
		CDBG("%s index %d\n", __func__, index);
		power_setting = &ctrl->power_setting[index];
		CDBG("%s type %d\n", __func__, power_setting->seq_type);
		switch (power_setting->seq_type) {
		case SENSOR_CLK:
			if (power_setting->seq_val >= ctrl->clk_info_size) {
				pr_err_ratelimited("%s clk %d >=max %zu\n"
					, __func__,
					power_setting->seq_val,
					ctrl->clk_info_size);
				goto power_up_failed;
			}
			if (power_setting->config_val)
				ctrl->clk_info[power_setting->seq_val]
					.clk_rate = power_setting->config_val;
			rc = msm_camera_clk_enable(ctrl->dev,
				ctrl->clk_info, ctrl->clk_ptr,
				ctrl->clk_info_size, true);
			if (rc < 0) {
				pr_err_ratelimited("%s: clk enable failed\n",
					__func__);
				goto power_up_failed;
			}
			break;
		case SENSOR_GPIO:
			if (no_gpio) {
				pr_err("%s: request gpio failed\n", __func__);
				return no_gpio;
			}
			if (power_setting->seq_val >= SENSOR_GPIO_MAX ||
				!ctrl->gpio_conf->gpio_num_info) {
				pr_err("%s gpio index %d >= max %d\n", __func__,
					power_setting->seq_val,
					SENSOR_GPIO_MAX);
				goto power_up_failed;
			}
			if (!ctrl->gpio_conf->gpio_num_info->valid
				[power_setting->seq_val])
				continue;
			CDBG("%s:%d gpio set val %d\n", __func__, __LINE__,
				ctrl->gpio_conf->gpio_num_info->gpio_num
				[power_setting->seq_val]);
			gpio_set_value_cansleep(
				ctrl->gpio_conf->gpio_num_info->gpio_num
				[power_setting->seq_val],
				(int) power_setting->config_val);
			break;
		case SENSOR_VREG:
			if (power_setting->seq_val == INVALID_VREG)
				break;

			if (power_setting->seq_val >= CAM_VREG_MAX) {
				pr_err("%s vreg index %d >= max %d\n", __func__,
					power_setting->seq_val,
					SENSOR_GPIO_MAX);
				goto power_up_failed;
			}
			if (power_setting->seq_val < ctrl->num_vreg)
				msm_camera_config_single_vreg(ctrl->dev,
					&ctrl->cam_vreg
					[power_setting->seq_val],
					(struct regulator **)
					&power_setting->data[0],
					1);
			else
				pr_err("%s: %d usr_idx:%d dts_idx:%d\n",
					__func__, __LINE__,
					power_setting->seq_val, ctrl->num_vreg);

			rc = msm_cam_sensor_handle_reg_gpio(
				power_setting->seq_val,
				ctrl->gpio_conf, 1);
			if (rc < 0) {
				pr_err("ERR:%s Error in handling VREG GPIO\n",
					__func__);
				goto power_up_failed;
			}
			break;
		case SENSOR_I2C_MUX:
			if (ctrl->i2c_conf && ctrl->i2c_conf->use_i2c_mux)
				msm_camera_enable_i2c_mux(ctrl->i2c_conf);
			break;
		default:
			pr_debug("%s error power seq type %d\n", __func__,
				power_setting->seq_type);
			break;
		}
		if (power_setting->delay > 20) {
			msleep(power_setting->delay);
		} else if (power_setting->delay) {
			usleep_range(power_setting->delay * 1000,
				(power_setting->delay * 1000) + 1000);
		}
	}

	if (device_type == MSM_CAMERA_PLATFORM_DEVICE) {
		rc = sensor_i2c_client->i2c_func_tbl->i2c_util(
			sensor_i2c_client, MSM_CCI_INIT);
		if (rc < 0) {
			pr_err("%s cci_init failed\n", __func__);
			goto power_up_failed;
		}
	}
	CDBG("%s exit\n", __func__);
	return 0;
power_up_failed:
	pr_err_ratelimited("%s:%d failed\n", __func__, __LINE__);
	for (index--; index >= 0; index--) {
		CDBG("%s index %d\n", __func__, index);
		power_setting = &ctrl->power_setting[index];
		CDBG("%s type %d\n", __func__, power_setting->seq_type);
		switch (power_setting->seq_type) {
		case SENSOR_GPIO:
			if (!ctrl->gpio_conf->gpio_num_info)
				continue;
			if (!ctrl->gpio_conf->gpio_num_info->valid
				[power_setting->seq_val])
				continue;
			gpio_set_value_cansleep(
				ctrl->gpio_conf->gpio_num_info->gpio_num
				[power_setting->seq_val], GPIOF_OUT_INIT_LOW);
			break;
		case SENSOR_VREG:
			if (power_setting->seq_val < ctrl->num_vreg)
				msm_camera_config_single_vreg(ctrl->dev,
					&ctrl->cam_vreg
					[power_setting->seq_val],
					(struct regulator **)
					&power_setting->data[0],
					0);
			else
				pr_err("%s:%d:seq_val: %d > num_vreg: %d\n",
					__func__, __LINE__,
					power_setting->seq_val, ctrl->num_vreg);

			msm_cam_sensor_handle_reg_gpio(power_setting->seq_val,
				ctrl->gpio_conf, GPIOF_OUT_INIT_LOW);
			break;
		case SENSOR_I2C_MUX:
			if (ctrl->i2c_conf && ctrl->i2c_conf->use_i2c_mux)
				msm_camera_disable_i2c_mux(ctrl->i2c_conf);
			break;
		default:
			pr_debug("%s error power seq type %d\n", __func__,
				power_setting->seq_type);
			break;
		}
		if (power_setting->delay > 20) {
			msleep(power_setting->delay);
		} else if (power_setting->delay) {
			usleep_range(power_setting->delay * 1000,
				(power_setting->delay * 1000) + 1000);
		}
	}
	if (ctrl->cam_pinctrl_status) {
		ret = pinctrl_select_state(ctrl->pinctrl_info.pinctrl,
				ctrl->pinctrl_info.gpio_state_suspend);
		if (ret)
			pr_err("%s:%d cannot set pin to suspend state\n",
				__func__, __LINE__);
		devm_pinctrl_put(ctrl->pinctrl_info.pinctrl);
	}
	ctrl->cam_pinctrl_status = 0;
	msm_camera_request_gpio_table(
		ctrl->gpio_conf->cam_gpio_req_tbl,
		ctrl->gpio_conf->cam_gpio_req_tbl_size, 0);
	return rc;
}

static struct msm_sensor_power_setting*
msm_camera_get_power_settings(struct msm_camera_power_ctrl_t *ctrl,
				enum msm_sensor_power_seq_type_t seq_type,
				uint16_t seq_val)
{
	struct msm_sensor_power_setting *power_setting, *ps = NULL;
	int idx;

	for (idx = 0; idx < ctrl->power_setting_size; idx++) {
		power_setting = &ctrl->power_setting[idx];
		if (power_setting->seq_type == seq_type &&
			power_setting->seq_val ==  seq_val) {
			ps = power_setting;
			return ps;
		}

	}
	return ps;
}

int msm_camera_power_down(struct msm_camera_power_ctrl_t *ctrl,
	enum msm_camera_device_type_t device_type,
	struct msm_camera_i2c_client *sensor_i2c_client)
{
	int index = 0, ret = 0;
	struct msm_sensor_power_setting *pd = NULL;
	struct msm_sensor_power_setting *ps;

	CDBG("%s:%d\n", __func__, __LINE__);
	if (!ctrl || !sensor_i2c_client) {
		pr_err("failed ctrl %pK sensor_i2c_client %pK\n", ctrl,
			sensor_i2c_client);
		return -EINVAL;
	}
	if (device_type == MSM_CAMERA_PLATFORM_DEVICE)
		sensor_i2c_client->i2c_func_tbl->i2c_util(
			sensor_i2c_client, MSM_CCI_RELEASE);

	for (index = 0; index < ctrl->power_down_setting_size; index++) {
		CDBG("%s index %d\n", __func__, index);
		pd = &ctrl->power_down_setting[index];
		ps = NULL;
		CDBG("%s type %d\n", __func__, pd->seq_type);
		switch (pd->seq_type) {
		case SENSOR_CLK:
			msm_camera_clk_enable(ctrl->dev,
				ctrl->clk_info, ctrl->clk_ptr,
				ctrl->clk_info_size, false);
				break;
		case SENSOR_GPIO:
			if (pd->seq_val >= SENSOR_GPIO_MAX ||
				!ctrl->gpio_conf->gpio_num_info) {
				pr_err("%s gpio index %d >= max %d\n", __func__,
					pd->seq_val,
					SENSOR_GPIO_MAX);
				continue;
			}
			if (!ctrl->gpio_conf->gpio_num_info->valid
				[pd->seq_val])
				continue;
			gpio_set_value_cansleep(
				ctrl->gpio_conf->gpio_num_info->gpio_num
				[pd->seq_val],
				(int) pd->config_val);
			break;
		case SENSOR_VREG:
			if (pd->seq_val == INVALID_VREG)
				break;
			if (pd->seq_val >= CAM_VREG_MAX) {
				pr_err("%s vreg index %d >= max %d\n", __func__,
					pd->seq_val,
					SENSOR_GPIO_MAX);
				continue;
			}

			ps = msm_camera_get_power_settings(ctrl,
						pd->seq_type,
						pd->seq_val);
			if (ps) {
				if (pd->seq_val < ctrl->num_vreg)
					msm_camera_config_single_vreg(ctrl->dev,
						&ctrl->cam_vreg
						[pd->seq_val],
						(struct regulator **)
						&ps->data[0],
						0);
				else
					pr_err("%s:%d:seq_val:%d > num_vreg: %d\n",
						__func__, __LINE__, pd->seq_val,
						ctrl->num_vreg);
			} else
				pr_err("%s error in power up/down seq data\n",
								__func__);
			ret = msm_cam_sensor_handle_reg_gpio(pd->seq_val,
				ctrl->gpio_conf, GPIOF_OUT_INIT_LOW);
			if (ret < 0)
				pr_err("ERR:%s Error while disabling VREG GPIO\n",
					__func__);
			break;
		case SENSOR_I2C_MUX:
			if (ctrl->i2c_conf && ctrl->i2c_conf->use_i2c_mux)
				msm_camera_disable_i2c_mux(ctrl->i2c_conf);
			break;
		default:
			pr_debug("%s error power seq type %d\n", __func__,
				pd->seq_type);
			break;
		}
		if (pd->delay > 20) {
			msleep(pd->delay);
		} else if (pd->delay) {
			usleep_range(pd->delay * 1000,
				(pd->delay * 1000) + 1000);
		}
	}
	if (ctrl->cam_pinctrl_status) {
		ret = pinctrl_select_state(ctrl->pinctrl_info.pinctrl,
				ctrl->pinctrl_info.gpio_state_suspend);
		if (ret)
			pr_err("%s:%d cannot set pin to suspend state\n",
				__func__, __LINE__);
		devm_pinctrl_put(ctrl->pinctrl_info.pinctrl);
	}
	ctrl->cam_pinctrl_status = 0;
	msm_camera_request_gpio_table(
		ctrl->gpio_conf->cam_gpio_req_tbl,
		ctrl->gpio_conf->cam_gpio_req_tbl_size, 0);
	CDBG("%s exit\n", __func__);
	return 0;
}
