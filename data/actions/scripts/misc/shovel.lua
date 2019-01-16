function onUse(player, item, fromPosition, target, toPosition)
	local tile = Tile(toPosition)
	if not tile then
		return false
	end

	local ground = tile:getGround()
	if not ground then
		return false
	end
	
	local toTarget = target;
	
	local itemType = ItemType(target:getId())
	if itemType:isSplash() then
		toTarget = ground
	end
	
	if toTarget:getId() == 231 then 
		toTarget:getPosition():sendMagicEffect(3)
		return true
	elseif toTarget:getId() == 593 then 
		toTarget:transform(594, 1)
		toTarget:decay()
		doRelocate(toTarget:getPosition(), toTarget:getPosition():moveRel(0,0,1))
		return true
	elseif toTarget:getId() == 606 then 
		toTarget:transform(607, 1)
		toTarget:decay()
		doRelocate(toTarget:getPosition(), toTarget:getPosition():moveRel(0,0,1))
		return true
	elseif toTarget:getId() == 608 then 
		toTarget:transform(609, 1)
		toTarget:decay()
		doRelocate(toTarget:getPosition(), toTarget:getPosition():moveRel(0,0,1))
	elseif toTarget:getId() == 614 and math.random(1, 100) <= 50 then
		toTarget:transform(615, 1)
		toTarget:decay()
		toTarget:getPosition():sendMagicEffect(3)
		doRelocate(toTarget:getPosition(), toTarget:getPosition():moveRel(0,0,1))
	elseif toTarget:getId() == 614 then
		toTarget:getPosition():sendMagicEffect(3)
	elseif toTarget:getId() == 616 and math.random(1, 100) <= 95 then
		toTarget:transform(617, 1)
		toTarget:decay()
		toTarget:getPosition():sendMagicEffect(3)
		Game.createMonster("scarab", toTarget:getPosition())
	elseif toTarget:getId() == 616 then
		toTarget:getPosition():sendMagicEffect(3)
		Game.createItem(3042, 1, toTarget:getPosition())
		toTarget:transform(617, 1)
		toTarget:decay()
	elseif toTarget:getId() == 617 then
		toTarget:getPosition():sendMagicEffect(3)
	end
	return false
end
