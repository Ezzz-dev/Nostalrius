local downstairs = {
	435
}

local upstairs = {
	1948, 1968
}

function onUse(player, item, fromPosition, target, toPosition)
	if table.contains(downstairs, item:getId()) then
		player:teleportTo(item:getPosition():moveRel(0, 0, 1))
	elseif table.contains(upstairs, item:getId()) then
		player:teleportTo(item:getPosition():moveRel(0, 1, -1))
	end
	return true
end
