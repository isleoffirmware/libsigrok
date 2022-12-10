/*
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <unistd.h>
#include <config.h>
#include "protocol.h"

#define ASCII_0 (48U)
#define ASCII_9 (57U)

SR_PRIV int virtual_receive_data(int fd, int revents, void *cb_data)
{
	const struct sr_dev_inst *sdi;
	struct dev_context *devc;
	struct sr_datafeed_logic logic;
	struct sr_datafeed_packet packet;
	uint8_t data = 0;

	(void)fd;

	if (!(sdi = cb_data) || !(devc = sdi->priv))
		return TRUE;

	if (!(sdi = cb_data))
		return TRUE;

	if (!(devc = sdi->priv))
		return TRUE;

	if (revents == G_IO_IN) {
		// NOTE: only read 1 byte for now
		if (read(devc->fd, &data, 1) != 1)
			return TRUE;

		// only parse ASCII 0-9
		// NOTE: getting ASCII LF from shell script
		if ((data < ASCII_0) || (data > ASCII_9))
			return TRUE;

		data = data - ASCII_0;

		logic.data = &data;
		logic.length = 1;
		logic.unitsize = 1;

		packet.type = SR_DF_LOGIC; // NOTE: only supporting LA for now
		packet.payload = &logic;

		sr_session_send(sdi, &packet);
	}

	return TRUE;
}
