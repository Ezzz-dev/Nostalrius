function onLogin(player)
	local loginStr = "Welcome to " .. configManager.getString(configKeys.SERVER_NAME) .. "!"
	if player:getLastLoginSaved() <= 0 then
		loginStr = loginStr .. " Please choose your outfit."
		player:sendOutfitWindow()
	else
		if loginStr ~= "" then
			player:sendTextMessage(MESSAGE_STATUS_DEFAULT, loginStr)
		end

		loginStr = string.format("Your last visit on Nostalrius: %s.", os.date("%a %b %d %X %Y", player:getLastLoginSaved()))
	end
	player:sendTextMessage(MESSAGE_STATUS_DEFAULT, loginStr)

	-- Promotion
	if player:isPremium() then
		if player:getVocation():getId() ~= 0 and player:getVocation():getId() < 5 and player:getStorageValue(30018) == 1 then
			player:setVocation(player:getVocation():getId() + 4)
		end
	else
		if player:getVocation():getId() ~= 0 and player:getVocation():getId() > 4 then
			player:setVocation(player:getVocation():getId() - 4)
		end
	end
	
	-- Outfits
	if not player:isPremium() then
		if player:getSex() == PLAYERSEX_FEMALE then
			local outfit = player:getOutfit()
			if outfit.lookType > 139 then
				player:setOutfit({lookType = 136, lookHead = 78, lookBody = 106, lookLegs = 58, lookFeet = 95})
			end
		else
			local outfit = player:getOutfit()
			if outfit.lookType > 131 then
				player:setOutfit({lookType = 128, lookHead = 78, lookBody = 106, lookLegs = 58, lookFeet = 95})
			end
		end
	end

	-- Premium system
	if player:isPremium() then
		player:setStorageValue(43434, 1)
	elseif player:getStorageValue(43434) == 1 then
		player:setStorageValue(43434, 0)
		player:teleportTo({x = 32369, y = 32241, z = 7})
		player:setTown(Town("Thais"))
	end
	
	-- Events
	player:registerEvent("PlayerDeath")
	player:registerEvent("kills")
	return true
end
