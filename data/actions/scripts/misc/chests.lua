function onUse(player, item, fromPosition, target, toPosition)
	local chestQuestNumber = item:getAttribute(ITEM_ATTRIBUTE_CHESTQUESTNUMBER)
	
	if player:getStorageValue(chestQuestNumber) > 0 then
		player:sendTextMessage(MESSAGE_INFO_DESCR, "The " .. item:getName() .. " is empty.")
		return true
	end
	
	local playerCapacity = player:getFreeCapacity()

	if item:getSize() <= 0 then
		player:sendTextMessage(MESSAGE_INFO_DESCR, "The chest is empty. This is a bug, report it to a gamemaster.")
		return true
	end
	
	local reward = item:getItem(0)
	local stackable = reward:getType():isStackable()
	local rewardName = reward:getName()
	local rewardWeight = reward:getWeight()

	if stackable then
		if reward:getCount() > 1 then
			rewardName = reward:getCount() .. " " .. reward:getPluralName()
		else
			rewardName = reward:getName()
		end
	end
	
	if reward:getArticle():len() > 0 and reward:getCount() <= 1 then
		rewardName = reward:getArticle() .. " " .. rewardName
	end
	
	if rewardWeight > playerCapacity and not getPlayerFlagValue(player, layerFlag_HasInfiniteCapacity) then
		local term = "it is"
		if stackable and reward:getCount() > 1 then
			term = "they are"
		end
		
		player:sendTextMessage(MESSAGE_INFO_DESCR, string.format("You have found %s. Weighing %d.%02d oz %s too heavy.", rewardName, rewardWeight / 100, rewardWeight % 100, term))
		return true
	end
	
	player:sendTextMessage(MESSAGE_INFO_DESCR, "You have found " .. rewardName .. ".")
	player:addItemEx(reward:clone(), true)
	if not getPlayerFlagValue(player, PlayerFlag_HasInfiniteCapacity) then
		player:setStorageValue(chestQuestNumber, 1)
	end
	return true
end
