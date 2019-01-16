function onStepIn(creature, item, position, fromPosition)
	if not creature:isPlayer() then
		return true
	end
	
	local player = Player(creature)
	local lookPosition = player:getPosition()
	lookPosition:getNextPosition(player:getDirection())
	local depotItem = Tile(lookPosition):getItemByType(ITEM_TYPE_DEPOT)
	if depotItem ~= nil then
		local depotItems = player:getDepotChest(getDepotId(depotItem:getUniqueId()), true):getItemHoldingCount()
		player:sendTextMessage(MESSAGE_STATUS_DEFAULT, "Your depot contains " .. depotItems .. " item" .. (depotItems > 1 and "s." or "."))
	end
	
	if item:getId() == 431 then
		item:transform(430)
	elseif item:getId() == 419 then
		item:transform(420)
	elseif item:getId() == 452 then
		item:transform(453)
	elseif item:getId() == 563 then
		item:transform(564)
	end
end

function onStepOut(creature, item, position, fromPosition)
	if item:getId() == 430 then
		item:transform(431)
	elseif item:getId() == 420 then
		item:transform(419)
	elseif item:getId() == 453 then
		item:transform(452)
	elseif item:getId() == 564 then
		item:transform(563)
	end
end
