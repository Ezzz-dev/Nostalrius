function onUse(player, item, fromPosition, target, toPosition)
	if player:hasFlag(PlayerFlag_SpecialMoveUse) then
		if item:getId() == 372 then
			item:transform(394, 1)
			item:decay()
		elseif item:getId() == 386 or item:getId() == 421 then
			local relPos = item:getPosition():moveRel(0, 1, -1)
			player:teleportTo(relPos)
		elseif item:getId() == 593 then
			item:transform(594, 1)
			item:decay()
			doRelocate(item:getPosition(),item:getPosition():moveRel(0, 0, 1))
		elseif item:getId() == 606 or item:getId() == 608 then
			item:transform(607, 1)
			item:decay()
			doRelocate(item:getPosition(), item:getPosition():moveRel(0, 0, 1))
		elseif item:getId() == 614 then
			item:transform(615, 1)
			item:decay()
			item:getPosition():sendMagicEffect(3)
			doRelocate(item:getPosition(), item:getPosition():moveRel(0, 0, 1))
		elseif item:getId() == 3653 then
			item:transform(3651, 1)
			item:decay()
			Game.createItem(3605, 1, item:getPosition())
		elseif item:getId() == 3696 then
			item:transform(3695, 1)
			item:decay()
		elseif item:getId() == 3702 then
			item:transform(3701, 1)
			item:decay()
		end
	else
		return false
	end
	return true
end
